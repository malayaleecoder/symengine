#include "catch.hpp"
#include <iostream>
#include <chrono>

#include <symengine/functions.h>
#include <symengine/integer.h>
#include <symengine/rational.h>
#include <symengine/symbol.h>
#include <symengine/add.h>
#include <symengine/pow.h>
#include <symengine/series.h>

using SymEngine::Basic;
using SymEngine::Integer;
using SymEngine::integer;
using SymEngine::rational;
using SymEngine::Symbol;
using SymEngine::Number;
using SymEngine::symbol;
using SymEngine::Add;
using SymEngine::rcp_static_cast;
using SymEngine::RCP;
using SymEngine::add;
using SymEngine::sin;
using SymEngine::cos;
using SymEngine::series;

TEST_CASE("Expression series expansion interface", "[Expansion interface]")
{
    RCP<const Symbol> x = symbol("x"), y = symbol("y");
    auto ex = div(integer(1), add(integer(1), x));

//! TODO: remove this ifdef when we have a generic implementation of series
#if defined(HAVE_SYMENGINE_PIRANHA) || defined(HAVE_SYMENGINE_FLINT)
    auto ser = series(ex, x, 10);

    REQUIRE(rcp_static_cast<const Number>(ser->get_coeff(7))->is_minus_one());
    REQUIRE(rcp_static_cast<const Number>(ser->as_dict()[8])->is_one());
    REQUIRE(ser->as_basic()->__str__()=="1 - x + x**2 - x**3 + x**4 - x**5 + x**6 - x**7 + x**8 - x**9");
#else
    REQUIRE_THROWS_AS(series(ex, x, 10), std::runtime_error);
#endif
}
