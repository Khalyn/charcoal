#include <iostream>

#include "message_box.hpp"
#include "temperature.hpp"


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


template<CTemperature T>
constexpr void display_current_temperature( T const &temperature )
{
	printf( "Temperature: %.2f%s\n", temperature.as_inner(), T::UNIT );
}

int main()
{
	constexpr Celsius celsius( 15.0f );
	constexpr Fahrenheit fahrenheit = celsius_to_fahrenheit( celsius );
	display_current_temperature( fahrenheit );
	display_current_temperature( celsius );

	display_msgbox_example();
    return 0;
}
