// crypto5.cpp : Defines the entry point for the console application.
//

#include <cmath>
#include <iostream>
#include <gmpxx.h>
#include <utility>
#include <vector>
#include <map>


using namespace std;


map<mpz_class, mpz_class>  BuildHash(mpz_class& g, mpz_class& h, mpz_class& p, mpz_class& max)
{
    map<mpz_class, mpz_class> multProducts;
    for (mpz_class i = 1; i <= max; i++)
	{
        mpz_class product;
        mpz_powm(product.get_mpz_t() , g.get_mpz_t(), i.get_mpz_t(), p.get_mpz_t());
        mpz_class hInverse;
        mpz_invert(hInverse.get_mpz_t(), product.get_mpz_t(), p.get_mpz_t());
        hInverse *= h;
        mpz_mod(hInverse.get_mpz_t(), hInverse.get_mpz_t(), p.get_mpz_t());
        multProducts.insert(pair<mpz_class, mpz_class>(hInverse, i));
	}

	return multProducts;
}

int main(int argc, char* argv[])
{\

    mpz_class p("13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084171");
    mpz_class g("11717829880366207009516117596335367088558084999998952205599979459063929499736583746670572176471460312928594829675428279466566527115212748467589894601965568");
    mpz_class h("3239475104050450443565264378728065788649097520952449527834792452971981976143292558073856937958553180532878928001494706097394108577585732452307673444020333");
    mpz_class B;
    mpz_ui_pow_ui(B.get_mpz_t(), 2, 20);

    map<mpz_class, mpz_class> hash = BuildHash(g, h, p, B);

    for (mpz_class i = 1; i <= B; i++)
    {
        //cout << "try" << i.get_str() << std::endl;
        mpz_class gToBX;
        mpz_powm(gToBX.get_mpz_t(), g.get_mpz_t(), mpz_class(B*i).get_mpz_t(), p.get_mpz_t());
        map<mpz_class, mpz_class>::iterator searchRes = hash.find(gToBX);

        if (searchRes != hash.end())
        {
            std::cout << "x1: " << searchRes->second.get_str() << " x0: " << i.get_str() << endl;
            mpz_class x(searchRes->second + i*B);
            mpz_mod(x.get_mpz_t(), x.get_mpz_t(), p.get_mpz_t());
            std::cout << "x: " << x.get_str() << endl;
            break;
        }
    }

	cin.get();
	return 0;
}

