#pragma once

#include <concepts>

namespace charcoal
{
	class boolean
	{
	public:
		using inner_type = bool;

		// constructors
		explicit constexpr boolean( bool const value ) : m_data( value ) {};
		constexpr boolean( boolean const &value ) = default;

		// operator overload
		explicit constexpr operator inner_type() const { return m_data; }


		// TODO methods
		[[nodiscard]] inline constexpr auto as_inner() const noexcept -> bool
		{
			return m_data;
		}

		[[nodiscard]] inline constexpr auto eq( boolean const &rhs ) const noexcept -> boolean
		{
			return boolean( this->m_data == rhs.m_data );
		}


		[[nodiscard]] inline constexpr auto ne( boolean const &rhs ) const noexcept -> boolean
		{
			return boolean( this->m_data != rhs.m_data );
		}


	private:
		inner_type m_data;
	};

	static inline constexpr boolean const True( true );
	static inline constexpr boolean const False( false );


	template<typename T> struct is_boolean : std::false_type {};
	template<> struct is_boolean<boolean> : std::true_type {};
	template<> struct is_boolean<boolean const> : std::true_type {};
	template<> struct is_boolean<boolean volatile> : std::true_type {};
	template<> struct is_boolean<boolean const volatile> : std::true_type {};

	template<typename T>
	constexpr inline bool is_boolean_v = is_boolean<T>::value;


	inline namespace tests_ct
	{
		static_assert( sizeof( boolean ) == sizeof( bool ) );
		static_assert( True );
		static_assert( not False );
		static_assert( not not True );

		inline namespace tests_ct_eq_ne
		{
			consteval auto testing_eq() -> boolean
			{
				boolean const value1( True );
				boolean const value2( []() consteval -> auto { return False; } () );

				return value1.ne( value2 );
			}
			static_assert( testing_eq() );

			consteval auto testing_ne() -> boolean
			{
				boolean const value1( True );
				boolean const value2( []() consteval -> auto { return True; } () );

				return value1.eq( value2 );
			}
			static_assert( testing_ne() );
		}
	}; // inline namespace tests_ct

}; // namespace charcoal
