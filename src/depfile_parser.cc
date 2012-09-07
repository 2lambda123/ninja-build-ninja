/* Generated by re2c 0.13.5 */
// Copyright 2011 Google Inc. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "depfile_parser.h"

// A note on backslashes in Makefiles, from reading the docs:
// Backslash-newline is the line continuation character.
// Backslash-# escapes a # (otherwise meaningful as a comment start).
// Backslash-% escapes a % (otherwise meaningful as a special).
// Finally, quoting the GNU manual, "Backslashes that are not in danger
// of quoting ‘%’ characters go unmolested."
// How do you end a line with a backslash?  The netbsd Make docs suggest
// reading the result of a shell command echoing a backslash!
//
// Rather than implement all of above, we do a simpler thing here:
// Backslashes escape a set of characters (see "escapes" defined below),
// otherwise they are passed through verbatim.
// If anyone actually has depfiles that rely on the more complicated
// behavior we can adjust this.
bool DepfileParser::Parse(string* content, string* err) {
  // in: current parser input point.
  // end: end of input.
  // parsing_targets: whether we are parsing targets or dependencies.
  char* in = &(*content)[0];
  char* end = in + content->size();
  bool parsing_targets = true;
  while (in < end) {
    // out: current output point (typically same as in, but can fall behind
    // as we de-escape backslashes).
    char* out = in;
    // filename: start of the current parsed filename.
    char* filename = out;
    for (;;) {
      // start: beginning of the current parsed span.
      const char* start = in;
      
    {
      char yych;
      static const unsigned char yybm[] = {
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
        128, 128,   0, 128, 128, 128, 128, 128, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128,   0,   0, 128,   0,   0, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128,   0,   0,   0,   0, 128, 
          0, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128, 128, 128, 128, 128, 128, 
        128, 128, 128,   0,   0,   0, 128,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
          0,   0,   0,   0,   0,   0,   0,   0, 
      };

      yych = *in;
      if (yych <= 'Z') {
        if (yych <= '*') {
          if (yych <= 0x00) goto yy6;
          if (yych <= '\'') goto yy8;
          if (yych <= ')') goto yy4;
          goto yy8;
        } else {
          if (yych <= '<') {
            if (yych <= ':') goto yy4;
            goto yy8;
          } else {
            if (yych <= '=') goto yy4;
            if (yych <= '?') goto yy8;
            goto yy4;
          }
        }
      } else {
        if (yych <= '_') {
          if (yych == '\\') goto yy2;
          if (yych <= '^') goto yy8;
          goto yy4;
        } else {
          if (yych <= 'z') {
            if (yych <= '`') goto yy8;
            goto yy4;
          } else {
            if (yych == '~') goto yy4;
            goto yy8;
          }
        }
      }
yy2:
      ++in;
      if ((yych = *in) <= '$') {
        if (yych <= '\n') {
          if (yych <= 0x00) goto yy3;
          if (yych <= '\t') goto yy11;
        } else {
          if (yych == ' ') goto yy13;
          if (yych <= '"') goto yy11;
          goto yy13;
        }
      } else {
        if (yych <= 'Z') {
          if (yych == '*') goto yy13;
          goto yy11;
        } else {
          if (yych <= '\\') goto yy13;
          if (yych == '|') goto yy13;
          goto yy11;
        }
      }
yy3:
      {
        // For any other character (e.g. whitespace), swallow it here,
        // allowing the outer logic to loop around again.
        break;
      }
yy4:
      ++in;
      yych = *in;
      goto yy10;
yy5:
      {
        // Got a span of plain text.
        int len = (int)(in - start);
        // Need to shift it over if we're overwriting backslashes.
        if (out < start)
          memmove(out, start, len);
        out += len;
        continue;
      }
yy6:
      ++in;
      {
        break;
      }
yy8:
      yych = *++in;
      goto yy3;
yy9:
      ++in;
      yych = *in;
yy10:
      if (yybm[0+yych] & 128) {
        goto yy9;
      }
      goto yy5;
yy11:
      ++in;
      {
        // Let backslash before other characters through verbatim.
        *out++ = '\\';
        *out++ = yych;
        continue;
      }
yy13:
      ++in;
      {
        // De-escape backslashed character.
        *out++ = yych;
        continue;
      }
    }

    }

    int len = (int)(out - filename);
    const bool is_target = parsing_targets;
    if (len > 0 && filename[len - 1] == ':') {
      len--;  // Strip off trailing colon, if any.
      parsing_targets = false;
    }

    if (len == 0)
      continue;

    if (!is_target) {
      ins_.push_back(StringPiece(filename, len));
    } else if (!out_.str_) {
      out_ = StringPiece(filename, len);
    } else if (out_ != StringPiece(filename, len)) {
      *err = "depfile has multiple output paths.";
      return false;
    }
  }
  return true;
}
