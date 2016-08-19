RotateOperation = {}
RotateOperation.__index = RotateOperation

setmetatable(RotateOperation, {
    __index = Operations,
    __call = function (o, ...)
        local self = setmetatable({}, o)
        self:_init(...)
        return self
    end,
})

function RotateOperation:_init(id)
    Operations._init(self, id)

    self.selection = active_widget():selection()

    message(tostring(#self.selection) .. " items selected")

    if(#self.selection > 0) then
        self.origin = nil
        self.firstPoint = nil
        self.secondPoint = nil

        self.tempEntities = {}

        event.register('point', self)
        event.register('mouseMove', self)

        message("Give origin point")
    else
        self.finished = true
        event.trigger('operationFinished')
    end
end

function RotateOperation:onEvent(eventName, ...)
    if(Operations.forMe(self) == false) then
        return
    end

    if(eventName == "point" or eventName == "number") then
        self:newData(...)
    elseif(eventName == "mouseMove") then
        self:tempRotate(...)
    end
end

function RotateOperation:newData(point)
    if(self.origin == nil) then
        self.origin = Operations:getCoordinate(point)

        message("Give first point")
    elseif(self.firstPoint == nil) then
        self.firstPoint = Operations:getCoordinate(point)

        message("Give second point")
    elseif(Operations:getCoordinate(point) ~= nil) then
        self.secondPoint = Operations:getCoordinate(point)

        self:rotate()
    end
end

function RotateOperation:tempRotate(point)
    if(self.origin ~= nil and self.firstPoint ~= nil) then
        for k, entity in pairs(self.tempEntities) do
            active_widget():tempEntities():removeEntity(entity)
        end
        self.tempEntities = {}

        local angle = self.origin:angleTo(point) - self.origin:angleTo(self.firstPoint)

        for k, entity in pairs(self.selection) do
            local newEntity = entity:rotate(self.origin, angle)
            active_widget():tempEntities():addEntity(newEntity)
            table.insert(self.tempEntities, newEntity)
        end
    end
end

function RotateOperation:rotate()
    local angle = self.origin:angleTo(self.secondPoint) - self.origin:angleTo(self.firstPoint)
    local b = Builder(active_widget():document())

    for k, entity in pairs(self.selection) do
        b:append(entity)
    end

    b:push()
    b:rotate(self.origin, angle)
    b:execute()

    self:close()
end

function RotateOperation:close()
    if(not self.finished) then
        self.finished = true

        for k, entity in pairs(self.tempEntities) do
            active_widget():tempEntities():removeEntity(entity)
        end

        event.delete('mouseMove', self)
        event.delete('point', self)

        event.trigger('operationFinished')
    end
end