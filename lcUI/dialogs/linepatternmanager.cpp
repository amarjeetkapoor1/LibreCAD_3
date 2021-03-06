#include "linepatternmanager.h"
#include "ui_linepatternmanager.h"

LinePatternManager::LinePatternManager(lc::Document_SPtr document, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LinePatternManager),
    _model(new LinePatternModel(this)) {

    ui->setupUi(this);

    setDocument(document);

    ui->lpView->setModel(_model);
    ui->lpView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->lpView->horizontalHeader()->setSectionResizeMode(LinePatternModel::NAME, QHeaderView::Stretch);

    show();
}

LinePatternManager::~LinePatternManager() {
    delete ui;
    delete _model;
}

void LinePatternManager::setDocument(lc::Document_SPtr document) {
    if(_document != nullptr) {
        _document->addLinePatternEvent().disconnect<LinePatternManager, &LinePatternManager::on_addLinePatternEvent>(this);
        _document->removeLinePatternEvent().disconnect<LinePatternManager, &LinePatternManager::on_removeLinePatternEvent>(this);
        _document->replaceLinePatternEvent().disconnect<LinePatternManager, &LinePatternManager::on_replaceLinePatternEvent>(this);
    }

    _document = document;

    if(_document != nullptr) {
        _document->addLinePatternEvent().connect<LinePatternManager, &LinePatternManager::on_addLinePatternEvent>(this);
        _document->removeLinePatternEvent().connect<LinePatternManager, &LinePatternManager::on_removeLinePatternEvent>(this);
        _document->replaceLinePatternEvent().connect<LinePatternManager, &LinePatternManager::on_replaceLinePatternEvent>(this);
    }

    updateModel();
}

void LinePatternManager::on_editButton_pressed() {
    QItemSelectionModel* select = ui->lpView->selectionModel();
    if(!select->hasSelection()) {
        return;
    }

    auto row = select->selectedRows().first().row();
    auto linePattern = _model->linePatternAt(row);

    auto dialog = new AddLinePatternDialog(_document, linePattern, this);
    dialog->show();
}

void LinePatternManager::on_newButton_pressed() {
    auto dialog = new AddLinePatternDialog(_document, this);
    dialog->show();
}

void LinePatternManager::on_lpView_doubleClicked(const QModelIndex &index) {
    if(!index.isValid()) {
        return;
    }

    auto linePattern = _model->linePatternAt(index.row());

    auto dialog = new AddLinePatternDialog(_document, linePattern, this);
    dialog->show();
}

void LinePatternManager::updateModel() {
    _model->setLinePatterns(_document->linePatterns());
}

void LinePatternManager::on_addLinePatternEvent(const lc::AddLinePatternEvent &) {
    updateModel();
}

void LinePatternManager::on_removeLinePatternEvent(const lc::RemoveLinePatternEvent &) {
    updateModel();
}

void LinePatternManager::on_replaceLinePatternEvent(const lc::ReplaceLinePatternEvent &) {
    updateModel();
}