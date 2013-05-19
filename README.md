EK - command line params generator
==================================

Ek generates C++ code from the usage string of a console application. The generated code makes all the input parameters available to the application as static members of the generated class.

Usage String Syntax
-------------------

The format of the usage string that Ek accepts is influenced by the PowerShell help content. Following are the command line params:

### Flags

The flags are specified as `[-FlagName]` in the usage string.

### Parameters

A parameter can be specified in any of the following ways:

1. `[-ParamName <param value help text>]`

	The presence of square brackets makes a parameter property optional. Here, `ParamName` is an optional parameter and the generated code would not terminate with error if the user does not provide `ParamName` value at the time of invoking the associate console application.

2. `[-ParamName] <param value help text>`

	`ParamName` is optional here, but the parameter value is not. Therefore, the command line can pass this value without specifying `-ParamName`.

3. `-ParamName <param value help text>`

	There are no optional parts to this parameter. This parameter value should be specified by the user always, and with the `-ParamName` specifier.


Examples
--------

1. `shutdown [-m] [-k] [-comp] <computer name> -timer <number in seconds>`

	This shows a usage string with four parameters. Two are flags, `-m`, and `-k`. Two others are parameters. Please note that value of timer always needs to be specified by `-Timer`, but passing a string would be assumed to be `computer name` without always requiring its specifier `-comp`.

