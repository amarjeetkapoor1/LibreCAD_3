op = {}

--Create empty new window
function new_file()
    new_document()
end

--Create open file dialog, and create a new window containing this file
function open_file()
    local fileName = qt.QFileDialog.getOpenFileName(
        mainWindow,
        qt.QObject.tr("Open File"),
        qt.QString(""),
        qt.QObject.tr("dxf(*.dxf);;dwg(*.dwg)")
    )

    if(not fileName:isEmpty()) then
        new_document(fileName:toStdString())
    end
end

--Create save file dialog and save the file
function save_file()
    if(active_widget() == nil) then
        return
    end

    local fileName = qt.QFileDialog.getSaveFileName(
        mainWindow,
        qt.QObject.tr("Save File"),
        qt.QString(""),
        qt.QObject.tr("dxf(*.dxf);;dwg(*.dwg)")
    )

    if(not fileName:isEmpty()) then
        if(active_widget() == nil) then
            return
        end

        active_widget():exportDXF(fileName:toStdString(), 6)
    end
end

--Return the selected layer
function active_layer()
    return layers:activeLayer()
end

--Create MetaInfo containing every selected MetaTypes
function active_metaInfo()
    local metaInfo = MetaInfo()

    local linePattern = linePatternSelect:linePattern()
    if(linePattern ~= nil) then
        metaInfo:addDxfLinePattern(linePattern)
    end

    local lineWidth = lineWidthSelect:lineWidth()
    if(lineWidth ~= nil) then
        metaInfo:add(lineWidth)
    end

    local color = colorSelect:metaColor()
    if(color ~= nil) then
        metaInfo:add(color)
    end

    return metaInfo
end

--Create dialog to enter Lua script
local function open_lua_script()
    local luaScript = lc.LuaScript(mdiArea, cliCommand)
    luaScript:show()
end

--Called when a new window is focused, and refreshes all the widgets
local function onSubWindowChanged(window)
    local document = active_document()

    --setDocument called without parameters to use nullptr
    if(document == nil) then
        layers:setDocument()
        linePatternSelect:setDocument()
    else
        layers:setDocument(document)
        linePatternSelect:setDocument(document)
    end
end

--Create main window menu
local function create_menu()
    local menuBar = mainWindow:menuBar()
    local drawMenu = menuBar:addMenuStr(qt.QString("Draw"))
    local lineAction = drawMenu:addActionStr(qt.QString("Line"))
    local circleAction = drawMenu:addActionStr(qt.QString("Circle"))
    local arcAction = drawMenu:addActionStr(qt.QString("Arc"))

    local luaMenu = menuBar:addMenuStr(qt.QString("Lua"))
    local luaScriptAction = luaMenu:addActionStr(qt.QString("Run script"))

    luaInterface:luaConnect(mainWindow:findChild("actionNew"), "triggered(bool)", new_file)
    luaInterface:luaConnect(mainWindow:findChild("actionOpen"), "triggered(bool)", open_file)
    luaInterface:luaConnect(mainWindow:findChild("actionSave_2"), "triggered(bool)", save_file)
    luaInterface:luaConnect(mainWindow:findChild("actionSave_As"), "triggered(bool)", save_file)
    luaInterface:luaConnect(mainWindow:findChild("actionUndo"), "triggered(bool)", undo)
    luaInterface:luaConnect(mainWindow:findChild("actionRedo"), "triggered(bool)", redo)

    luaInterface:luaConnect(lineAction, "triggered(bool)", create_line)
    luaInterface:luaConnect(circleAction, "triggered(bool)", create_circle)
    luaInterface:luaConnect(arcAction, "triggered(bool)", create_arc)

    luaInterface:luaConnect(luaScriptAction, "triggered(bool)", open_lua_script)
end

--Create main window and show it if required
function create_main_window()
    mainWindow = qt.loadUi(ui_path .. "/mainwindow.ui")
    mainWindow:setWindowTitle(qt.QObject.tr("LibreCAD"));
    mainWindow:setUnifiedTitleAndToolBarOnMac(true);

    mdiArea = mainWindow:findChild("centralWidget"):findChild("mdiArea")
    luaInterface:luaConnect(mdiArea, "subWindowActivated(QMdiSubWindow*)", onSubWindowChanged)

    mdiArea:setHorizontalScrollBarPolicy(0)
    mdiArea:setVerticalScrollBarPolicy(0)

    mainWindow:setCentralWidget(mdiArea)

    create_menu()

    add_commandline()

    layers = lc.Layers(active_document())
    mainWindow:addDockWidget(2, layers)

    linePatternSelect = lc.LinePatternSelect(mainWindow, true, true)
    lineWidthSelect = lc.LineWidthSelect(mainWindow, true, true)
    colorSelect = lc.ColorSelect(mainWindow, true, true)

    luaInterface:connect(layers, "layerChanged(lc::Layer_CSPtr)", linePatternSelect, "onLayerChanged(lc::Layer_CSPtr)")
    luaInterface:connect(layers, "layerChanged(lc::Layer_CSPtr)", lineWidthSelect, "onLayerChanged(lc::Layer_CSPtr)")
    luaInterface:connect(layers, "layerChanged(lc::Layer_CSPtr)", colorSelect, "onLayerChanged(lc::Layer_CSPtr)")

    add_toolbar()

    if(hideUI ~= true) then
        mainWindow:showMaximized()
    end

    new_file()
end

--Get next available index in the table
--It's used to store the CadMdiChild ids
function nextTableId(table)
    count = 0
    for id, v in pairs(table) do
        count = count + 1
        if(v == nil) then
            return count
        end
    end

    return count
end