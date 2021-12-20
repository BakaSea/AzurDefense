#pragma once
#include "Widget.h"
#include "ButtonCancel.h"
#include "ButtonConfirm.h"

class ButtonInfo : public Widget {
public:
	ButtonInfo(string infoName, ButtonCancel* btnCancel, ButtonConfirm* btnConfirm);
	void render() override;

private:
	string infoName;
};
