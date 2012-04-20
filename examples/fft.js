#include "include/complex.h"

#define sin Math.sin
#define cos Math.cos
#define pi Math.PI
#define fn function
#define CVECDIV(_v, _i, _n) _v[(_i) + 0] /= (_n), _v[(_i) + 1] /= (_n);

/*
 A simple, slow and unoptimized FFT for JS.
 Only works with powers of 2 sized arrays.
 Takes N (=12) as argument, where array size is 2^N.
 WARNING: Probably not suitable for any real world use!
 This has never been tested either.
*/

var FFT = this.FFT = (fn(){

var pi2 = pi * 2;

fn pass2 (input, output, inverse, product) {
	var k, j, i, k1, p;
	var size = input.length * 0.5;
	var factor = 2;
	var m = size / factor;
	var q = size / product;
	var product1 = product / factor;
	var jump = (factor - 1) * product1;

	var twi = Complex();
	var z0 = Complex();
	var z1 = Complex();
	var x0, x1, temp;

	for (k=j=i=0; k < q; k++, j += jump) {
		p = (inverse ? pi2 : -pi2) * k / q / factor;
		twi.assign(cos(p), sin(p));

		for (k1=0; k1 < product1; k1++, i++, j++) {
			z0.assign(input, 2 * i);
			z1.assign(input, 2 * (i + m));

			x0 = z0.add(z1);
			x1 = z0.sub(z1);
			temp = twi.mul(x1);

			x0.cp2arr(input, 2 * j);
			temp.cp2arr(input, 2 * (j + product1));
		}
	}
}

fn fft (value, scratch, N, inverse) {
	var inp, out, i;
	var product = 1;
	var state = 0;
	var size = value.length * .5;

	for (i=0; i<N; i++) {
		product *= 2;

		if (state) {
			inp = scratch;
			out = value;
			state = 0;
		} else {
			inp = value;
			out = scratch;
			state = 1;
		}

		pass2(inp, out, inverse, product);
	}

	if (inverse) {
		if (state === 1) {
			for (i=0; i<size; i++) {
				value[2 * i + 0] = scratch[2 * i + 0];
				value[2 * i + 1] = scratch[2 * i + 1];
			}
		}
	} else {
		for (i=0; i<size; i++) {
			CVECDIV(value, 2 * i, size);
		}
	}
}

fn FFT () {
	this.reset.apply(this, arguments);
}

FFT.prototype = {
	scratch: null,
	N: 12,

	reset: fn (N) {
		this.N = ~~(N) || this.N;

		/* Use typed arrays if available, if not, fall back to normal arrays. */
		try {
			this.scratch = new Float64Array(1 << this.N);
		} catch (e) {
			this.scratch = Array(1 << this.N);

			for (var i=0; i<this.scratch.length; i++) {
				this.scratch[i] = 0;
			}
		}
	},

	process: fn (input, inverse) {
		fft(input, this.scratch, this.N, inverse);
	}
};

FFT.fft = fft;

return FFT;

}());
