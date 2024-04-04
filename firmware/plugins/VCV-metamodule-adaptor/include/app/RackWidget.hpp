#pragma once
#include <app/CableWidget.hpp>
#include <app/ModuleWidget.hpp>
#include <app/ParamWidget.hpp>
#include <app/PortWidget.hpp>
#include <app/RailWidget.hpp>
#include <app/common.hpp>
#include <history.hpp>
#include <ui/Menu.hpp>
#include <widget/FramebufferWidget.hpp>
#include <widget/OpaqueWidget.hpp>

#include <set>

namespace rack::app
{

struct RackWidget : widget::OpaqueWidget {
	ParamWidget *touchedParam = nullptr;

	// clang-format off
	widget::Widget *getModuleContainer(){ return {}; }
	widget::Widget *getCableContainer(){ return {}; }
	math::Vec getMousePos(){ return {}; }

	void clear(){}
	void mergeJson(json_t *rootJ){}
	void fromJson(json_t *rootJ){}
	void pasteJsonAction(json_t *rootJ){}
	void pasteModuleJsonAction(json_t *moduleJ){}
	void pasteClipboardAction(){}

	void addModule(ModuleWidget *mw){}
	void addModuleAtMouse(ModuleWidget *mw){}
	void removeModule(ModuleWidget *mw){}
	ModuleWidget *getModule(int64_t moduleId) { return nullptr; }
	std::vector<ModuleWidget *> getModules(){ return {}; }
	bool hasModules(){ return {}; }

	bool requestModulePos(ModuleWidget *mw, math::Vec pos){ return {}; }
	void setModulePosNearest(ModuleWidget *mw, math::Vec pos){}
	void setModulePosForce(ModuleWidget *mw, math::Vec pos){}
	void setModulePosSqueeze(ModuleWidget *mw, math::Vec pos){}
	void updateModuleOldPositions(){}
	history::ComplexAction *getModuleDragAction(){ return {}; }

	void updateSelectionFromRect(){}
	void selectAll(){}
	void deselectAll(){}
	void select(ModuleWidget *mw, bool selected = true){}
	bool hasSelection(){ return {}; }
	std::set<ModuleWidget*> selected;
	const std::set<ModuleWidget *> &getSelected(){ return selected; }
	bool isSelected(ModuleWidget *mw){ return {}; }
	json_t *selectionToJson(bool cables = true){ return {}; }
	void loadSelection(std::string path){}
	void loadSelectionDialog(){}
	void saveSelection(std::string path){}
	void saveSelectionDialog(){}
	void copyClipboardSelection(){}
	void resetSelectionAction(){}
	void randomizeSelectionAction(){}
	void disconnectSelectionAction(){}
	void cloneSelectionAction(bool cloneCables = true){}
	void bypassSelectionAction(bool bypassed){}
	bool isSelectionBypassed(){ return {}; }
	void deleteSelectionAction(){}
	bool requestSelectionPos(math::Vec delta){ return {}; }
	void setSelectionPosNearest(math::Vec delta){}
	void appendSelectionContextMenu(ui::Menu *menu){}

	void clearCables(){}
	void clearCablesAction(){}
	void clearCablesOnPort(PortWidget *port){}
	void addCable(CableWidget *cw){}
	void removeCable(CableWidget *cw){}
	CableWidget *getIncompleteCable(){ return {}; }
	void setIncompleteCable(CableWidget *cw){}
	CableWidget *releaseIncompleteCable(){ return {}; }
	CableWidget *getTopCable(PortWidget *port){ return {}; }
	CableWidget *getCable(int64_t cableId){ return {}; }
	std::vector<CableWidget *> getCompleteCables(){ return {}; }
	std::vector<CableWidget *> getCablesOnPort(PortWidget *port){ return {}; }
	std::vector<CableWidget *> getCompleteCablesOnPort(PortWidget *port){ return {}; }
	int getNextCableColorId(){ return {}; }
	void setNextCableColorId(int id){}
	NVGcolor getNextCableColor(){ return {}; }
	ParamWidget *getTouchedParam(){ return {}; }
	void setTouchedParam(ParamWidget *pw){}
	// clang-format on
};

} // namespace rack::app
