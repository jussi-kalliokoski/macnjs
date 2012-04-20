#ifndef _CLASSES_H_
#define _CLASSES_H_

#define class(_name) function _name () { return _name.prototype.construct.apply(this, arguments); }\
	_name.prototype = 

#define extends(_parent, _child) void function () {\
	var key, old = _child.prototype;\
	for (key in _parent) {\
		if ({}.hasOwnProperty.call(_parent, key))\
			_child[key] = _parent[key];\
	}\
	function ctor() {\
		this.constructor = _child;\
	}\
	ctor.prototype = _parent.prototype; _child.prototype = new ctor;\
	_child.__super__ = _parent;\
	for (key in old) {\
		if ({}.hasOwnProperty.call(old, key))\
			_child.prototype[key] = old[key];\
	}\
}()

#define super(...) this.constructor.__super__.apply(this, arguments)

#endif
