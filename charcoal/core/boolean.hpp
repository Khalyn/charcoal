#pragma once

namespace charcoal
{
	class boolean
	{
	public:
		using inner_type = bool;

		// constructors
		explicit constexpr boolean( bool const value )
			: m_data( value )
		{};

		constexpr boolean( boolean const &value ) = default;

		// operator overload
		explicit constexpr operator inner_type() const { return m_data; }

		// TODO methods
	private:
		inner_type m_data;
	};

	static inline constexpr boolean const True( true );
	static inline constexpr boolean const False( false );

	inline namespace tests_ct
	{
		static_assert( sizeof( boolean ) == sizeof( bool ) );
		static_assert( True );
		static_assert( not False );
	}; // namespace tests_ct

}; // namespace charcoal
