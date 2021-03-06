#include "stdafx.h"
#include "../modern_graphics_lib.h"
#include "../ModernGraphicsClassAdapter.h"
#include <sstream>

using namespace std;
using namespace modern_graphics_lib;

struct ClassAdapterFixture
{
	ClassAdapterFixture()
		: out(),
		expectedOut(),
		renderer(expectedOut),
		adapter(out)
	{}

	ostringstream out;
	ostringstream expectedOut;
	CModernGraphicsRenderer renderer;
	ModernGraphicsClassAdapter adapter;

};

BOOST_FIXTURE_TEST_SUITE(ModernGraphicsClassAdapter_, ClassAdapterFixture)
	BOOST_AUTO_TEST_SUITE(after_construction)
		BOOST_AUTO_TEST_CASE(do_not_change_stream)
		{
			BOOST_CHECK_EQUAL(out.str(), "");
		}
	BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_CASE(can_draw_lines_in_modern_graphics_style)
	{
		adapter.BeginDraw();
		adapter.MoveTo(1, 1);
		adapter.LineTo(2, 2);
		adapter.LineTo(-1, -2);
		adapter.EndDraw();

		renderer.BeginDraw();
		renderer.DrawLine({ 1,1 }, { 2,2 });
		renderer.DrawLine({ 2,2 }, { -1,-2 });
		renderer.EndDraw();

		BOOST_CHECK_EQUAL(out.str(), expectedOut.str());
	}
BOOST_AUTO_TEST_SUITE_END()