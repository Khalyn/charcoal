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


constexpr void display_current_temperature( CTemperature auto const &temperature )
{
	printf( "Temperature: %.2f%s\n", temperature.as_inner(), temperature.UNIT );
}

struct A { float add() const { return 0.f; } };
struct B
{
	static constexpr u32 BYTES = u32( 1u );
	static constexpr u32 BITS = u32( BYTES * 8 );

	constexpr void SerializeBool( char *, boolean &bb ) { }
	constexpr void SerializeU32( char *, u32 &bb ) { }

	bool a = true;
};

using namespace std;
template<typename T> concept CInterface =
requires ( T &test )
{
	// Variables
	requires is_same_v<decltype( T::BYTES ), u32 const>;
	requires is_same_v<decltype( T::BITS ), u32 const>;

	// Methods
	{ test.SerializeBool( declval<char *>(), declval<boolean&>() ) } -> same_as<void>;
	{ test.SerializeU32( declval<char*>(), declval<u32&>() ) } -> same_as<void>;
};

static_assert(CInterface<B>);

constexpr void xxx( CInterface auto const &test )
{
}


int main()
{
	constexpr Celsius celsius( 15.0f );
	constexpr Fahrenheit fahrenheit = celsius_to_fahrenheit( celsius );
	display_current_temperature<Fahrenheit>( fahrenheit );
	display_current_temperature( celsius );

	display_msgbox_example();
	A a;
	B b;
	xxx( b );

    return 0;
}
