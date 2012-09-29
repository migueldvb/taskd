////////////////////////////////////////////////////////////////////////////////
// taskd - Task Server
//
// Copyright 2010 - 2012, Göteborg Bit Factory.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// http://www.opensource.org/licenses/mit-license.php
//
////////////////////////////////////////////////////////////////////////////////

#include <taskd.h>
#include <text.h>

////////////////////////////////////////////////////////////////////////////////
int command_init (Config& config, const std::vector <std::string>& args)
{
  int status = 0;

  // Standard argument processing.
  bool verbose     = true;
  bool debug       = false;
  std::string root = "";

  std::vector <std::string>::const_iterator i;
  for (i = ++(args.begin ()); i != args.end (); ++i)
  {
         if (closeEnough ("--quiet",  *i, 3)) verbose = false;
    else if (closeEnough ("--debug",  *i, 3)) debug   = true;
    else if (closeEnough ("--data",   *i, 3)) root    = *(++i);
    else if (taskd_applyOverride (config, *i))   ;
    else
      throw std::string ("ERROR: Unrecognized argument '") + *i + "'";
  }

  // Verify that root exists.
  if (root == "")
    throw std::string ("The '--data' option is required.");

  Directory root_dir (root);
  if (!root_dir.exists ())
    throw std::string ("The '--data' path does not exist.");

  if (!root_dir.is_directory ())
     throw std::string ("The '--data' path is not a directory.");
 
  if (!root_dir.readable ())
    throw std::string ("The '--data' directory is not readable.");
 
  if (!root_dir.writable ())
    throw std::string ("The '--data' directory is not writable.");
 
  if (!root_dir.executable ())
    throw std::string ("The '--data' directory is not executable.");
 
  // Create the data structure.
  Directory sub (root_dir);
  sub.cd ();
  sub += "orgs";
  if (!sub.create ())
    throw std::string ("Could not create '") + sub._data + "'.";

  // TODO Dump the config file?

  return status;
}

////////////////////////////////////////////////////////////////////////////////
