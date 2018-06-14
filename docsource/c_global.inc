Global functions and data
=========================

Functions
---------

======================  =======================================================
Function                Description
----------------------  -------------------------------------------------------
:c:func:`hat_list`      Return a list of detected MCC HAT boards.
======================  =======================================================

.. doxygenfunction:: hat_list

Data types and definitions
--------------------------

.. doxygendefine:: MAX_NUMBER_HATS

HAT IDs
~~~~~~~

.. doxygenenum:: HatIDs

Result Codes
~~~~~~~~~~~~

.. doxygenenum:: ResultCode

HatInfo structure
~~~~~~~~~~~~~~~~~

.. doxygenstruct:: HatInfo
    :members:

Analog Input / Scan Options
~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. doxygendefine:: OPTS_NOSCALEDATA
.. doxygendefine:: OPTS_NOCALIBRATEDATA
.. doxygendefine:: OPTS_EXTCLOCK
.. doxygendefine:: OPTS_EXTTRIGGER
.. doxygendefine:: OPTS_CONTINUOUS