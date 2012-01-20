Build the C link
================================
.. class:: subtitle

    Nikhil Marathe

.. raw:: pdf

    PageBreak cutePage

Introduction
------------

* V8 is a powerful, **fast** JavaScript engine
* It is self contained and easy to embed

      JS is the new Lua?

* node.js is a thin wrapper around V8 and evented I/O (*libuv*)

Code
----

\
\
\

    git clone git://github.com/nikhilm/jsfoo-pune-2012.git

We want to
------------

.. role:: large

\

\

\

\

\

\


:large:`Use C/C++ libraries in node.js`
\

\

\

:large:`Exchange data between C++ ⇔ JS`
\

\

\

:large:`Do asynchronous I/O`

Getting started
---------------

.. code-block:: cpp
    :include: firststep/firststep.cc

Build
-----

.. code-block:: python
    :include: firststep/wscript

Run
---

.. code-block:: bash

    $ node-waf configure build
    ...
    'build' finished successfully (0.327s)

    $ node

.. code-block:: js

    > require('./build/Release/firststep')
    {}

Architecture
------------

.. image:: images/architecture.png
    :width: 12cm

.. [#] you **will** need http://bespin.cz/~ondras/html/index.html

Handles
-----------

* Think of them as **smart pointers**, GCed by V8
* Also encode scope (Use `HandleScope` to manage handles)
* Local - GCed as they go out of scope::

    Local<String> name; // also Handle<...>

* Persistent - Must be manually disposed::

    Persistent<String> globalVariable;

Injecting primitives
--------------------

.. code-block:: cpp
    :include: primitives/primitives.cc


Simple functions
----------------

\
\
\
\
.. code-block:: js

    exports.square = function(n) {
        return n * n;
    }

\
We want to do this in C++

Simple functions
----------------

Registering with V8:

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-at: Handle<Value>
    :end-before: {

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-at: static void
    :end-before: NODE_MODULE

Simple functions
----------------

Implementation:

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-at: Handle
    :end-at: }

explain scope.Close

Templates
---------

.. code-block:: JS

    FunctionTemplate                          ???

    FunctionTemplate::GetFunction             square [Function]

    FunctionTemplate::InstanceTemplate        What `this` would be in 'new square()'

    FunctionTemplate::PrototypeTemplate       square.prototype

Calling JS functions
--------------------

.. code-block:: js
    :include: calljs/test.js

Calling JS functions
--------------------

.. code-block:: cpp
    :include: calljs/main.cc
    :start-at: Handle<Value>
    :end-before: extern


Simple objects
--------------

\
\
\

.. code-block:: js

    exports.Inventory = function() {
        this.items = 257;
    }

    // later
    var iv = new Inventory();
    console.log(iv.items);

This is the classic object oriented JS style

Simple objects
--------------

.. code-block:: cpp
    :include: simpleobject/main.cc
    :start-at: static void Init
    :end-before: NODE_MODULE

.. code-block:: cpp
    :include: simpleobject/main.cc
    :start-at: Handle<Value>
    :end-at: }

Methods
-------

.. code-block:: js

    Inventory.prototype.addStock = function(newStock) {
        this.items += newStock;
    }

    Inventory.prototype.ship = function(orders) {
        if (this.items < orders)
            throw Exception("Not enough items");

        this.items -= orders
    }

Methods
-------

Registering prototype methods

.. code-block:: cpp
    :include: methods/main.cc
    :start-at: // operating
    :end-at: GetFunction());

Methods
-------

Accessing object properties

.. code-block:: cpp
    :include: methods/main.cc
    :start-at: Handle<Value> AddStock
    :end-at: }

Methods
-------

Throwing an exception

.. code-block:: cpp
    :include: methods/main.cc
    :start-at: Handle<Value> Ship
    :end-at: }

ObjectWrap
----------

TODO diagram of how the nesting happens of native object and v8 object
and explain internal fields
TODO: args.Holder() vs args.This()
args.Holder() refers to the object it should've been called on
so that prototype chains work. Dig into NODE_SET_PROTOTYPE_METHOD
and explain Signatures

Going Async
-----------

Linking your library
--------------------

Linking external libs in Waf:

.. code-block:: python

    def configure(conf):
      # ...
      # uses pkg-config
      conf.check_cfg(package='<pkg-config name>', args='--cflags --libs',
      uselib_store='ALIAS')

    def build(bld):
      # ...
      obj.uselib = 'ALIAS'

Holder vs This
--------------

args.Holder() refers to the object it should've been called on
so that prototype chains work.

Strings to-and-fro
------------------

v8::String -> C string

.. code-block:: cpp
    :include: strings/main.cc
    :start-after: v8;
    :end-before: Handle<Value> Read

Strings to-and-fro
------------------

C string -> v8::String

.. code-block:: cpp
    :include: strings/main.cc
    :start-at: Handle<Value> Read
    :end-at: }

Things I haven't covered
------------------------

* Accessors
    * Per property accessors
    * Indexed accessors ( `object[5]` )
    * Named property accessors ( `object.property` )
* Function Signatures and HasInstance for type safety
* Emitting events using new JS only EventEmitter
* Details of libuv
* Using V8 on its own

You might want to look at
-------------------------

* https://github.com/weaver/uuidjs
* https://github.com/nikhilm/node-taglib
* https://github.com/pietern/hiredis-node

End notes
-----------

Contact:

* `@nikhilcutshort <https://twitter.com/nikhilcutshort>`_
* nsm.nikhil@gmail.com

\
\
\
`Cover image <http://www.flickr.com/photos/32045022@N05/3006326562/>`_ by `Munjal Savla <http://www.flickr.com/people/32045022@N05/>`_ (*by-nc-sa*)
