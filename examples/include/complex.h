#ifndef _COMPLEX_H_
#define _COMPLEX_H_

/* General use templates */

#define CMOD2(_r, _i) ((_r) * (_r) + (_i) * (_i))

#define CMOD(_r, _i) (Math.sqrt(CMOD2(_r, _i)))

#define CABS CMOD

#define CARG(_r, _i) (Math.atan2((_i), (_r)))

#define CISZERO(_r, _i) ((_r) === 0.0 && (_i) === 0.0)

#define CEQUALS(_r0, _i0, _r1, _i1) ((_r0) === (_r1) && (_i0) === (_i1))

#define CCONJUG_R(_r, _i) (_r)
#define CCONJUG_I(_r, _i) (-(_i))

#define CSQRT_R(_r, _i) (Math.sqrt(Math.abs(0.5 * (CMOD(_r, _i) + (_r)))))
#define CSQRT_I(_r, _i) (Math.sqrt(Math.abs(0.5 * (CMOD(_r, _i) - (_r)))))

#define CEXP_R(_r, _i) (Math.exp(_r) * Math.cos(_i))
#define CEXP_I(_r, _i) (Math.exp(_r) * Math.sin(_i))

#define CADD_R(_r0, _i0, _r1, _i1) ((_r0) + (_r1))
#define CADD_I(_r0, _i0, _r1, _i1) ((_i0) + (_i1))

#define CSUB_R(_r0, _i0, _r1, _i1) ((_r0) - (_r1))
#define CSUB_I(_r0, _i0, _r1, _i1) ((_i0) - (_i1))

#define CMUL_R(_r0, _i0, _r1, _i1) ((_r0) * (_r1) - (_i0) * (_i1))
#define CMUL_I(_r0, _i0, _r1, _i1) ((_i0) * (_r1) + (_r0) * (_i1))

#define CDIV_R(_r0, _i0, _r1, _i1) (((_r0) * (_r1) + (_i0) * (_i1)) / CMOD2(_r1, _i1))
#define CDIV_I(_r0, _i0, _r1, _i1) (((_i0) * (_r1) - (_r0) * (_i1)) / CMOD2(_r1, _i1))

/*
 Complex Type
 Very inefficient compared to using the macros directly.
*/

var Complex = (function () {

/* Preserve form and name even when minified */
var Complex = Function('return function Complex(r,i){}')();

function ComplexConstructor () {
	var c = new Complex();

	c.assign.apply(c, arguments);

	return c;
}

Complex.prototype = ComplexConstructor.prototype = {
	cp2arr: function (array, index) {
		array[i + 0] = this.r;
		array[i + 1] = this.i;
	},

	assign: function (r, i) {
		var rr = r, ii = i;

		if (arguments.length < 2) {
			i = 0;
		}
		if (arguments.length < 1) {
			r = 0;
		}

		if (r instanceof Complex) {
			rr = r.r;
			ii = r.i;
		} else if (r && r.length) {
			i = i || 0;
			rr = r[i + 0];
			ii = r[i + 1];
		}

		this.r = rr;
		this.i = ir;
	},

	mod2: function () {
		return CMOD2(this.r, this.i);
	},

	mod: function () {
		return CMOD(this.r, this.i);
	},

	arg: function () {
		return CARG(this.r, this.i);
	},

	isZero: function () {
		return CISZERO(this.r, this.i);
	},

	equals: function (c) {
		return CEQUALS(this.r, this.i, c.r, c.i);
	},

	conjug: function () {
		return ComplexConstructor(
			CCONJUG_R(this.r, this.i),
			CCONJUG_I(this.r, this.i)
		);
	},

	sqrt: function () {
		return ComplexConstructor(
			CSQRT_R(this.r, this.i),
			CSQRT_I(this.r, this.i)
		);
	},

	exp: function () {
		return ComplexConstructor(
			CEXP_R(this.r, this.i),
			CEXP_I(this.r, this.i)
		);
	},

	add: function (c) {
		return ComplexConstructor(
			CADD_R(this.r, this.i, c.r, c.i),
			CADD_I(this.r, this.i, c.r, c.i)
		);
		
	},

	sub: function (c) {
		return ComplexConstructor(
			CSUB_R(this.r, this.i, c.r, c.i),
			CSUB_I(this.r, this.i, c.r, c.i)
		);
		
	},

	mul: function (c) {
		return ComplexConstructor(
			CMUL_R(this.r, this.i, c.r, c.i),
			CMUL_I(this.r, this.i, c.r, c.i)
		);
	},

	div: function (c) {
		return ComplexConstructor(
			CDIV_R(this.r, this.i, c.r, c.i),
			CDIV_I(this.r, this.i, c.r, c.i)
		);
	}
};

return ComplexConstructor;

}());

#endif
