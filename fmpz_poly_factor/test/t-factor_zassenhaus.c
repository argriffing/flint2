/*=============================================================================

    This file is part of FLINT.

    FLINT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    FLINT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with FLINT; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA

=============================================================================*/
/******************************************************************************

    Copyright (C) 2010 Andy Novocin

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "flint.h"
#include "fmpz_poly.h"

int
main(void)
{
    int i, result;
    FLINT_TEST_INIT(state);

    flint_printf("zassenhaus....");
    fflush(stdout);

    

    for (i = 0; i < 10000; i++)
    {
        fmpz_t c;
        fmpz_poly_t f, g, h, t;
        fmpz_poly_factor_t fac;
        slong j, n = n_randint(state, 5);

        fmpz_init(c);
        fmpz_poly_init(f);
        fmpz_poly_init(g);
        fmpz_poly_init(h);
        fmpz_poly_init(t);
        fmpz_poly_factor_init(fac);

        fmpz_randtest_not_zero(c, state, n_randint(state, 10) + 1);
        fmpz_poly_set_fmpz(f, c);

        for (j = 0; j < n; j++)
        {
            fmpz_poly_randtest(g, state, n_randint(state, 5) + 2, n_randint(state, 40));
            fmpz_poly_mul(f, f, g);
        }
/*        fmpz_poly_set_str(f, "6  0 -1 0 0 0 1");*/

        fmpz_poly_factor_zassenhaus(fac, f);

        fmpz_poly_set_fmpz(h, &fac->c);
        for (j = 0; j < fac->num; j++)
        {
            if (fac->exp[j] == 1)
                fmpz_poly_mul(h, h, fac->p + j);
            else
            {
                fmpz_poly_pow(t, fac->p + j, fac->exp[j]);
                fmpz_poly_mul(h, h, t);
            }
        }

        result = fmpz_poly_equal(f, h);
        if (!result)
        {
            flint_printf("FAIL:\n");
            flint_printf("f = "), fmpz_poly_print(f), flint_printf("\n\n");
            flint_printf("h = "), fmpz_poly_print(h), flint_printf("\n\n");
            flint_printf("fac = "), fmpz_poly_factor_print(fac), flint_printf("\n\n");
            abort();
        }

        fmpz_clear(c);
        fmpz_poly_clear(f);
        fmpz_poly_clear(g);
        fmpz_poly_clear(h);
        fmpz_poly_clear(t);
        fmpz_poly_factor_clear(fac);
    }

    FLINT_TEST_CLEANUP(state);
    
    flint_printf("PASS\n");
    return 0;
}
