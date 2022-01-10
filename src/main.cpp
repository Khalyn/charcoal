#include "message_box.hpp"

void display_msgbox_example()
{
	MessageBoxContent content {};
	content.ownerHandle = nullptr;
	content.icon = MessageBoxIcon::Information;
	content.action = MessageBoxAction::YesNoCancel;
	content.defButton = MessageBoxDefButton::Button2;
	content.modality = MessageBoxModality::Application;
	content.settings = MessageBoxSettings::TopMost | MessageBoxSettings::RightJustified;
	content.title = "Title";
	content.body = "Do you really want to continue ?\n(Your choice doesn't really matter anyway)";
	message_box( content );
}


int main()
{
	display_msgbox_example();
    return 0;
}
