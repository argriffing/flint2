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

    Copyright (C) 2011 Fredrik Johansson
    Copyright (C) 2014 Abhinav Baid

******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include "flint.h"
#include "mpfr_mat.h"
#include "ulong_extras.h"

int
main(void)
{
    slong m, n, i, j, rep;
    FLINT_TEST_INIT(state);

    flint_printf("zero....");
    fflush(stdout);



    for (rep = 0; rep < 100 * flint_test_multiplier(); rep++)
    {
        mpfr_mat_t A;

        m = n_randint(state, 20);
        n = n_randint(state, 20);

        mpfr_mat_init(A, m, n, 200);

        mpfr_mat_randtest(A, state);
        mpfr_mat_zero(A);

        for (i = 0; i < m; i++)
        {
            for (j = 0; j < n; j++)
            {
                if (!mpfr_zero_p(mpfr_mat_entry(A, i, j)))
                {
                    flint_printf("FAIL: nonzero entry\n");
                    abort();
                }
            }
        }

        mpfr_mat_clear(A);
    }

    FLINT_TEST_CLEANUP(state);

    flint_printf("PASS\n");
    return 0;
}
