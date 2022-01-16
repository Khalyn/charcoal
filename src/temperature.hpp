#pragma once

#include <concepts>

#include "charcoal/core/primitives_types.hpp"
using namespace charcoal;


struct Celsius : public f32
{
	static constexpr char UNIT[] = "°C";
	static constexpr inner_type ABSOLUTE_ZERO = -273.15f;
	static constexpr inner_type WATER_FREEZING_POINT = 0.0f;
	static constexpr inner_type WATER_BOILING_POINT = 100.0f;

	explicit constexpr Celsius( type const &value ) : type( value ) {}
	explicit constexpr Celsius( inner_type const &value ) : type( value ) {}
};


struct Fahrenheit : public f32
{
	static constexpr char UNIT[] = "°F";
	static constexpr inner_type ABSOLUTE_ZERO = -459.67f;
	static constexpr inner_type WATER_FREEZING_POINT = 32.f;
	static constexpr inner_type WATER_BOILING_POINT = 212.f;

	explicit constexpr Fahrenheit( type const &value ) : type( value ) {}
	explicit constexpr Fahrenheit( inner_type const &value ) : type( value ) {}
};


struct Kelvin : public f32
{
	static constexpr char UNIT[] = "K";
	static constexpr inner_type ABSOLUTE_ZERO = 0.f;
	static constexpr inner_type WATER_FREEZING_POINT = 273.2f;
	static constexpr inner_type WATER_BOILING_POINT = 373.2f;

	explicit constexpr Kelvin( type const &value ) : type( value ) {}
	explicit constexpr Kelvin( inner_type const &value ) : type( value ) {}
};


// Celsius conversion
[[nodiscard]] constexpr auto celsius_to_fahrenheit( Celsius const &celsius ) -> Fahrenheit
{
	return Fahrenheit( celsius * 1.8f + 32.f );
}

[[nodiscard]] constexpr auto celsius_to_kelvin( Celsius const &celsius ) -> Kelvin
{
	return Kelvin( celsius - Celsius::ABSOLUTE_ZERO );
}

// Fahrenheit conversion
[[nodiscard]] constexpr auto fahrenheit_to_celsius( Fahrenheit const &fahrenheit ) -> Celsius
{
	return Celsius( ( fahrenheit - 32.f ) * 0.556f );
}

[[nodiscard]] constexpr auto fahrenheit_to_kelvin( Fahrenheit const &fahrenheit ) -> Kelvin
{
	return Kelvin( ( fahrenheit - 32.f ) * 0.556f + 273.15f );
}

// Kelvin conversion
[[nodiscard]] constexpr auto kelvin_to_celsius( Kelvin const &kelvin ) -> Celsius
{
	return Celsius( kelvin + Celsius::ABSOLUTE_ZERO  );
}

[[nodiscard]] constexpr auto kelvin_to_fahrenheit( Kelvin const &kelvin ) -> Fahrenheit
{
	return Fahrenheit( kelvin_to_celsius( kelvin ) * 1.8f + 32.f );
}



// Concept definition
template<typename T> struct is_temperature : std::false_type {};

// TODO : Simplify these override
template<> struct is_temperature<Celsius> : std::true_type {};
template<> struct is_temperature<Celsius const> : std::true_type {};
template<> struct is_temperature<Celsius volatile> : std::true_type {};
template<> struct is_temperature<Celsius const volatile> : std::true_type {};

template<> struct is_temperature<Fahrenheit> : std::true_type {};
template<> struct is_temperature<Fahrenheit const> : std::true_type {};
template<> struct is_temperature<Fahrenheit volatile> : std::true_type {};
template<> struct is_temperature<Fahrenheit const volatile> : std::true_type {};

template<> struct is_temperature<Kelvin> : std::true_type {};
template<> struct is_temperature<Kelvin const> : std::true_type {};
template<> struct is_temperature<Kelvin volatile> : std::true_type {};
template<> struct is_temperature<Kelvin const volatile> : std::true_type {};

template<typename T>
static constexpr bool is_temperature_v = is_temperature<T>::value;

template<typename T> concept CTemperature =
requires ( T temperature )
{
	requires is_temperature_v<T>;
	{ T::UNIT };
	{ T::ABSOLUTE_ZERO };
	{ T::WATER_FREEZING_POINT };
	{ T::WATER_BOILING_POINT };
};


inline namespace tests_ct
{
	inline namespace celsius
	{
		static_assert( sizeof( Celsius ) == sizeof( Fahrenheit ) );
		static_assert( sizeof( Celsius ) == sizeof( Kelvin ) );

		static_assert( Celsius::ABSOLUTE_ZERO == kelvin_to_celsius( Kelvin( Kelvin::ABSOLUTE_ZERO ) ).as_inner() );
		// TODO: Continue to write all necessary asserts.
	}
}; // namespace inline tests_ct
