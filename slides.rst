My V8 is binding TODO
=====================

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


Templates
---------

* Creation of functions and objects in C++

.. note::

    Explain how they differ, what each is for and
    whats the deal with FunctionTemplate && FunctionTemplate::GetFunction

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
    :start-at: Handle<Value>
    :end-at: }

.. code-block:: cpp
    :include: simpleobject/main.cc
    :start-at: static void Init
    :end-before: NODE_MODULE

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

Things I haven't covered
------------------------

* Accessors
    * Per property accessors
    * Indexed accessors ( `object[5]` )
    * Named property accessors ( `object.property` )
* Emitting events using new JS only EventEmitter
* Details of libuv
* Using V8 on its own

