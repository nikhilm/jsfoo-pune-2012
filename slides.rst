My V8 is binding TODO
=====================

.. class:: subtitle

    Nikhil Marathe

.. raw:: pdf

    PageBreak cutePage

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

Registering with V8:

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-at: Handle<Value>
    :end-before: {

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-at: static void
    :end-before: NODE_MODULE

TODO TODO TODO

Simple functions
----------------

Implementation:

.. code-block:: cpp
    :include: simplefunctions/main.cc
    :start-after: {
    :end-before: }

explain scope.Close

Simple objects
--------------

.. code-block:: cpp
    :include: simpleobject/main.cc
    :start-at: Handle<Value>
    :end-at: }

.. code-block:: cpp
    :include: simpleobject/main.cc
    :start-at: static void
    :end-at: }

TODO fix indentation in inclusion

ObjectWrap
----------

TODO diagram of how the nesting happens of native object and v8 object

MakeCallback
