#pragma once
#include <deque>
#include <vector>

#include <jansson.h>

#include <color.hpp>
#include <common.hpp>
#include <math.hpp>
#include <plugin/Model.hpp>

namespace rack
{

namespace app
{
struct ModuleWidget;
struct CableWidget;
} // namespace app

namespace history
{

struct Action {
	std::string name;
	virtual ~Action() = default;
	virtual void undo() {
	}
	virtual void redo() {
	}
};

template<class TAction>
struct InverseAction : TAction {
	void undo() override {
		TAction::redo();
	}
	void redo() override {
		TAction::undo();
	}
};

struct ComplexAction : Action {
	std::vector<Action *> actions;
	~ComplexAction() override;
	void undo() override;
	void redo() override;
	void push(Action *action);
	bool isEmpty();
};

/** An action operating on a module.
Subclass this to create your own custom actions for your module.
*/
struct ModuleAction : Action {
	int64_t moduleId = -1;
};

struct ModuleAdd : ModuleAction {
	plugin::Model *model{};
	math::Vec pos{};
	json_t *moduleJ{};
	ModuleAdd() {
		name = "add module";
	}
	~ModuleAdd() override;
	void setModule(app::ModuleWidget *mw);
	void undo() override;
	void redo() override;
};

struct ModuleRemove : InverseAction<ModuleAdd> {
	ModuleRemove() {
		name = "remove module";
	}
};

struct ModuleMove : ModuleAction {
	math::Vec oldPos;
	math::Vec newPos;
	void undo() override;
	void redo() override;
	ModuleMove() {
		name = "move module";
	}
};

struct ModuleBypass : ModuleAction {
	bool bypassed{};
	void undo() override;
	void redo() override;
	ModuleBypass() {
		name = "bypass module";
	}
};

struct ModuleChange : ModuleAction {
	json_t *oldModuleJ{};
	json_t *newModuleJ{};
	ModuleChange() {
		name = "change module";
	}
	~ModuleChange() override;
	void undo() override;
	void redo() override;
};

struct ParamChange : ModuleAction {
	int paramId{};
	float oldValue{};
	float newValue{};
	void undo() override;
	void redo() override;
	ParamChange() {
		name = "change parameter";
	}
};

struct CableAdd : Action {
	int64_t cableId{};
	int64_t inputModuleId{};
	int inputId{};
	int64_t outputModuleId{};
	int outputId{};
	NVGcolor color{};
	void setCable(app::CableWidget *cw);
	void undo() override;
	void redo() override;
	CableAdd() {
		name = "add cable";
	}
};

struct CableRemove : InverseAction<CableAdd> {
	CableRemove() {
		name = "remove cable";
	}
};

struct CableColorChange : Action {
	int64_t cableId{};
	NVGcolor newColor{};
	NVGcolor oldColor{};
	void setCable(app::CableWidget *cw);
	void undo() override;
	void redo() override;
	CableColorChange() {
		name = "change cable color";
	}
};

struct State {
	struct Internal;
	Internal *internal;

	std::deque<Action *> actions;
	int actionIndex;
	int savedIndex;

	PRIVATE State();
	PRIVATE ~State();
	PRIVATE void clear();
	void push(Action *action);
	void undo();
	void redo();
	bool canUndo();
	bool canRedo();
	std::string getUndoName();
	std::string getRedoName();
	void setSaved();
	bool isSaved();
};

} // namespace history
} // namespace rack
