#include "include/classes.h"

#define isUndefined(_varname) (typeof _varname === 'undefined')
#define defaultValue(_vara, _varb) (isUndefined(_vara) ? _varb : _vara)
#define fn function

class (Person) {
	name: 'John Doe',
	age: 30,

	construct: fn (name, age) {
		this.name = defaultValue(name, this.name);
		this.age = defaultValue(age, this.age);
	},

	say: fn (what) {
		console.log(this.name, 'says',  what);
	}
};

class (DeadPerson) {
	died: new Date(),

	construct: fn (name, age, died) {
		super();

		this.died = defaultValue(died, this.died);
	},

	say: fn () {
		console.log(this.name, "can't speak, he died", new Date() - this.died,
			'milliseconds ago, at the age of', this.age);
	},
};
extends(Person, DeadPerson);

var Matt = new Person("Matt Mattsson");
Matt.say('hi');

var Doug = new DeadPerson("Doug Dougers");
Doug.say('hi');
