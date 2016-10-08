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

#include "lexer.h"

#include <stdio.h>

#include "eval_env.h"
#include "util.h"

bool Lexer::Error(const string& message, string* err) {
  // Compute line/column.
  int line = 1;
  const char* context = input_.str_;
  for (const char* p = input_.str_; p < last_token_; ++p) {
    if (*p == '\n') {
      ++line;
      context = p + 1;
    }
  }
  int col = last_token_ ? (int)(last_token_ - context) : 0;

  char buf[1024];
  snprintf(buf, sizeof(buf), "%s:%d: ", filename_.AsString().c_str(), line);
  *err = buf;
  *err += message + "\n";

  // Add some context to the message.
  const int kTruncateColumn = 72;
  if (col > 0 && col < kTruncateColumn) {
    int len;
    bool truncated = true;
    for (len = 0; len < kTruncateColumn; ++len) {
      if (context[len] == 0 || context[len] == '\n') {
        truncated = false;
        break;
      }
    }
    *err += string(context, len);
    if (truncated)
      *err += "...";
    *err += "\n";
    *err += string(col, ' ');
    *err += "^ near here";
  }

  return false;
}

Lexer::Lexer(const char* input) {
  Start("input", input);
}

void Lexer::Start(StringPiece filename, StringPiece input) {
  filename_ = filename;
  input_ = input;
  ofs_ = input_.str_;
  last_token_ = NULL;
}

const char* Lexer::TokenName(Token t) {
  switch (t) {
  case ERROR:
    return "lexing error";
  case BUILD:
    return "'build'";
  case COLON:
    return "':'";
  case DEFAULT:
    return "'default'";
  case EQUALS:
    return "'='";
  case IDENT:
    return "identifier";
  case INCLUDE:
    return "'include'";
  case INDENT:
    return "indent";
  case NEWLINE:
    return "newline";
  case PIPE2:
    return "'||'";
  case PIPE:
    return "'|'";
  case POOL:
    return "'pool'";
  case RULE:
    return "'rule'";
  case SUBNINJA:
    return "'subninja'";
  case TEOF:
    return "eof";
  }
  return NULL;  // not reached
}

const char* Lexer::TokenErrorHint(Token expected) {
  switch (expected) {
  case COLON:
    return " ($ also escapes ':')";
  default:
    return "";
  }
}

string Lexer::DescribeLastError() {
  if (last_token_) {
    switch (last_token_[0]) {
    case '\t':
      return "tabs are not allowed, use spaces";
    }
  }
  return "lexing error";
}

void Lexer::UnreadToken() {
  ofs_ = last_token_;
}

Lexer::Token Lexer::ReadToken() {
  const char* p = ofs_;
  const char* q;
  const char* start;
  Lexer::Token token;
  for (;;) {
    start = p;

    {
      unsigned char yych;
      unsigned int yyaccept = 0;
      static const unsigned char yybm[] = {
        0,  64, 64, 64, 64, 64, 64, 64, 64, 64, 0,  64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 192, 64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 96, 96, 64, 96, 96, 96,  96, 96, 96,
        96, 96, 96, 96, 64, 64, 64, 64, 64, 64, 64, 96, 96, 96, 96,  96, 96, 96,
        96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96,  96, 96, 96,
        96, 64, 64, 64, 64, 96, 64, 96, 96, 96, 96, 96, 96, 96, 96,  96, 96, 96,
        96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96, 96,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,  64, 64, 64,
        64, 64, 64, 64,
      };

      yych = *p;
      if (yych <= 'Z') {
        if (yych <= '#') {
          if (yych <= '\f') {
            if (yych <= 0x00)
              goto yy23;
            if (yych == '\n')
              goto yy7;
            goto yy25;
          } else {
            if (yych <= 0x1F) {
              if (yych <= '\r')
                goto yy6;
              goto yy25;
            } else {
              if (yych <= ' ')
                goto yy2;
              if (yych <= '"')
                goto yy25;
              goto yy4;
            }
          }
        } else {
          if (yych <= '9') {
            if (yych <= ',')
              goto yy25;
            if (yych == '/')
              goto yy25;
            goto yy22;
          } else {
            if (yych <= '<') {
              if (yych <= ':')
                goto yy16;
              goto yy25;
            } else {
              if (yych <= '=')
                goto yy14;
              if (yych <= '@')
                goto yy25;
              goto yy22;
            }
          }
        }
      } else {
        if (yych <= 'i') {
          if (yych <= 'a') {
            if (yych == '_')
              goto yy22;
            if (yych <= '`')
              goto yy25;
            goto yy22;
          } else {
            if (yych <= 'c') {
              if (yych <= 'b')
                goto yy9;
              goto yy22;
            } else {
              if (yych <= 'd')
                goto yy13;
              if (yych <= 'h')
                goto yy22;
              goto yy20;
            }
          }
        } else {
          if (yych <= 'r') {
            if (yych == 'p')
              goto yy11;
            if (yych <= 'q')
              goto yy22;
            goto yy12;
          } else {
            if (yych <= 'z') {
              if (yych <= 's')
                goto yy21;
              goto yy22;
            } else {
              if (yych == '|')
                goto yy18;
              goto yy25;
            }
          }
        }
      }
    yy2:
      yyaccept = 0;
      yych = *(q = ++p);
      goto yy73;
    yy3 : {
      token = INDENT;
      break;
    }
    yy4:
      yyaccept = 1;
      yych = *(q = ++p);
      if (yych >= 0x01)
        goto yy68;
    yy5 : {
      token = ERROR;
      break;
    }
    yy6:
      yych = *++p;
      if (yych == '\n')
        goto yy65;
      goto yy5;
    yy7:
      ++p;
    yy8 : {
      token = NEWLINE;
      break;
    }
    yy9:
      ++p;
      if ((yych = *p) == 'u')
        goto yy60;
      goto yy27;
    yy10 : {
      token = IDENT;
      break;
    }
    yy11:
      yych = *++p;
      if (yych == 'o')
        goto yy56;
      goto yy27;
    yy12:
      yych = *++p;
      if (yych == 'u')
        goto yy52;
      goto yy27;
    yy13:
      yych = *++p;
      if (yych == 'e')
        goto yy45;
      goto yy27;
    yy14:
      ++p;
      {
        token = EQUALS;
        break;
      }
    yy16:
      ++p;
      {
        token = COLON;
        break;
      }
    yy18:
      ++p;
      if ((yych = *p) == '|')
        goto yy43;
      {
        token = PIPE;
        break;
      }
    yy20:
      yych = *++p;
      if (yych == 'n')
        goto yy36;
      goto yy27;
    yy21:
      yych = *++p;
      if (yych == 'u')
        goto yy28;
      goto yy27;
    yy22:
      yych = *++p;
      goto yy27;
    yy23:
      ++p;
      {
        token = TEOF;
        break;
      }
    yy25:
      yych = *++p;
      goto yy5;
    yy26:
      ++p;
      yych = *p;
    yy27:
      if (yybm[0 + yych] & 32) {
        goto yy26;
      }
      goto yy10;
    yy28:
      yych = *++p;
      if (yych != 'b')
        goto yy27;
      yych = *++p;
      if (yych != 'n')
        goto yy27;
      yych = *++p;
      if (yych != 'i')
        goto yy27;
      yych = *++p;
      if (yych != 'n')
        goto yy27;
      yych = *++p;
      if (yych != 'j')
        goto yy27;
      yych = *++p;
      if (yych != 'a')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = SUBNINJA;
        break;
      }
    yy36:
      yych = *++p;
      if (yych != 'c')
        goto yy27;
      yych = *++p;
      if (yych != 'l')
        goto yy27;
      yych = *++p;
      if (yych != 'u')
        goto yy27;
      yych = *++p;
      if (yych != 'd')
        goto yy27;
      yych = *++p;
      if (yych != 'e')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = INCLUDE;
        break;
      }
    yy43:
      ++p;
      {
        token = PIPE2;
        break;
      }
    yy45:
      yych = *++p;
      if (yych != 'f')
        goto yy27;
      yych = *++p;
      if (yych != 'a')
        goto yy27;
      yych = *++p;
      if (yych != 'u')
        goto yy27;
      yych = *++p;
      if (yych != 'l')
        goto yy27;
      yych = *++p;
      if (yych != 't')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = DEFAULT;
        break;
      }
    yy52:
      yych = *++p;
      if (yych != 'l')
        goto yy27;
      yych = *++p;
      if (yych != 'e')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = RULE;
        break;
      }
    yy56:
      yych = *++p;
      if (yych != 'o')
        goto yy27;
      yych = *++p;
      if (yych != 'l')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = POOL;
        break;
      }
    yy60:
      yych = *++p;
      if (yych != 'i')
        goto yy27;
      yych = *++p;
      if (yych != 'l')
        goto yy27;
      yych = *++p;
      if (yych != 'd')
        goto yy27;
      ++p;
      if (yybm[0 + (yych = *p)] & 32) {
        goto yy26;
      }
      {
        token = BUILD;
        break;
      }
    yy65:
      ++p;
      {
        token = NEWLINE;
        break;
      }
    yy67:
      ++p;
      yych = *p;
    yy68:
      if (yybm[0 + yych] & 64) {
        goto yy67;
      }
      if (yych >= 0x01)
        goto yy70;
    yy69:
      p = q;
      if (yyaccept <= 0) {
        goto yy3;
      } else {
        goto yy5;
      }
    yy70:
      ++p;
      { continue; }
    yy72:
      yyaccept = 0;
      q = ++p;
      yych = *p;
    yy73:
      if (yybm[0 + yych] & 128) {
        goto yy72;
      }
      if (yych <= '\f') {
        if (yych != '\n')
          goto yy3;
      } else {
        if (yych <= '\r')
          goto yy75;
        if (yych == '#')
          goto yy67;
        goto yy3;
      }
      yych = *++p;
      goto yy8;
    yy75:
      ++p;
      if ((yych = *p) == '\n')
        goto yy65;
      goto yy69;
    }
  }

  last_token_ = start;
  ofs_ = p;
  if (token != NEWLINE && token != TEOF)
    EatWhitespace();
  return token;
}

bool Lexer::PeekToken(Token token) {
  Token t = ReadToken();
  if (t == token)
    return true;
  UnreadToken();
  return false;
}

void Lexer::EatWhitespace() {
  const char* p = ofs_;
  const char* q;
  for (;;) {
    ofs_ = p;

    {
      unsigned char yych;
      static const unsigned char yybm[] = {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,   0, 0, 0,
      };
      yych = *p;
      if (yych <= ' ') {
        if (yych <= 0x00)
          goto yy82;
        if (yych <= 0x1F)
          goto yy84;
      } else {
        if (yych == '$')
          goto yy80;
        goto yy84;
      }
      ++p;
      yych = *p;
      goto yy92;
    yy79 : { continue; }
    yy80:
      yych = *(q = ++p);
      if (yych == '\n')
        goto yy85;
      if (yych == '\r')
        goto yy87;
    yy81 : { break; }
    yy82:
      ++p;
      { break; }
    yy84:
      yych = *++p;
      goto yy81;
    yy85:
      ++p;
      { continue; }
    yy87:
      yych = *++p;
      if (yych == '\n')
        goto yy89;
      p = q;
      goto yy81;
    yy89:
      ++p;
      { continue; }
    yy91:
      ++p;
      yych = *p;
    yy92:
      if (yybm[0 + yych] & 128) {
        goto yy91;
      }
      goto yy79;
    }
  }
}

bool Lexer::ReadIdent(string* out) {
  const char* p = ofs_;
  for (;;) {
    const char* start = p;

    {
      unsigned char yych;
      static const unsigned char yybm[] = {
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   128, 128, 0,   128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 0,   0,   0,   0,   0,   0,   0,   128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 0,   0,   0,   0,   128, 0,   128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
        0,   0,   0,   0,
      };
      yych = *p;
      if (yych <= '@') {
        if (yych <= '.') {
          if (yych <= ',')
            goto yy97;
        } else {
          if (yych <= '/')
            goto yy97;
          if (yych >= ':')
            goto yy97;
        }
      } else {
        if (yych <= '_') {
          if (yych <= 'Z')
            goto yy95;
          if (yych <= '^')
            goto yy97;
        } else {
          if (yych <= '`')
            goto yy97;
          if (yych >= '{')
            goto yy97;
        }
      }
    yy95:
      ++p;
      yych = *p;
      goto yy100;
    yy96 : {
      out->assign(start, p - start);
      break;
    }
    yy97:
      ++p;
      { return false; }
    yy99:
      ++p;
      yych = *p;
    yy100:
      if (yybm[0 + yych] & 128) {
        goto yy99;
      }
      goto yy96;
    }
  }
  ofs_ = p;
  EatWhitespace();
  return true;
}

bool Lexer::ReadEvalString(EvalString* eval, bool path, string* err) {
  const char* p = ofs_;
  const char* q;
  const char* start;
  for (;;) {
    start = p;

    {
      unsigned char yych;
      static const unsigned char yybm[] = {
        0,   128, 128, 128, 128, 128, 128, 128, 128, 128, 0,   128, 128, 0,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 16,  128, 128, 128, 0,   128, 128, 128, 128, 128,
        128, 128, 128, 224, 160, 128, 224, 224, 224, 224, 224, 224, 224, 224,
        224, 224, 0,   128, 128, 128, 128, 128, 128, 224, 224, 224, 224, 224,
        224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
        224, 224, 224, 224, 224, 224, 224, 128, 128, 128, 128, 224, 128, 224,
        224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224,
        224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 128, 0,   128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128, 128,
        128, 128, 128, 128,
      };
      yych = *p;
      if (yych <= ' ') {
        if (yych <= '\n') {
          if (yych <= 0x00)
            goto yy110;
          if (yych >= '\n')
            goto yy107;
        } else {
          if (yych == '\r')
            goto yy105;
          if (yych >= ' ')
            goto yy107;
        }
      } else {
        if (yych <= '9') {
          if (yych == '$')
            goto yy109;
        } else {
          if (yych <= ':')
            goto yy107;
          if (yych == '|')
            goto yy107;
        }
      }
      ++p;
      yych = *p;
      goto yy140;
    yy104 : {
      eval->AddText(StringPiece(start, p - start));
      continue;
    }
    yy105:
      ++p;
      if ((yych = *p) == '\n')
        goto yy137;
      {
        last_token_ = start;
        return Error(DescribeLastError(), err);
      }
    yy107:
      ++p;
      {
        if (path) {
          p = start;
          break;
        } else {
          if (*start == '\n')
            break;
          eval->AddText(StringPiece(start, 1));
          continue;
        }
      }
    yy109:
      yych = *++p;
      if (yych <= '-') {
        if (yych <= 0x1F) {
          if (yych <= '\n') {
            if (yych <= '\t')
              goto yy112;
            goto yy124;
          } else {
            if (yych == '\r')
              goto yy114;
            goto yy112;
          }
        } else {
          if (yych <= '#') {
            if (yych <= ' ')
              goto yy115;
            goto yy112;
          } else {
            if (yych <= '$')
              goto yy117;
            if (yych <= ',')
              goto yy112;
            goto yy119;
          }
        }
      } else {
        if (yych <= 'Z') {
          if (yych <= '9') {
            if (yych <= '/')
              goto yy112;
            goto yy119;
          } else {
            if (yych <= ':')
              goto yy121;
            if (yych <= '@')
              goto yy112;
            goto yy119;
          }
        } else {
          if (yych <= '`') {
            if (yych == '_')
              goto yy119;
            goto yy112;
          } else {
            if (yych <= 'z')
              goto yy119;
            if (yych <= '{')
              goto yy123;
            goto yy112;
          }
        }
      }
    yy110:
      ++p;
      {
        last_token_ = start;
        return Error("unexpected EOF", err);
      }
    yy112:
      ++p;
    yy113 : {
      last_token_ = start;
      return Error("bad $-escape (literal $ must be written as $$)", err);
    }
    yy114:
      yych = *++p;
      if (yych == '\n')
        goto yy134;
      goto yy113;
    yy115:
      ++p;
      {
        eval->AddText(StringPiece(" ", 1));
        continue;
      }
    yy117:
      ++p;
      {
        eval->AddText(StringPiece("$", 1));
        continue;
      }
    yy119:
      ++p;
      yych = *p;
      goto yy133;
    yy120 : {
      eval->AddSpecial(StringPiece(start + 1, p - start - 1));
      continue;
    }
    yy121:
      ++p;
      {
        eval->AddText(StringPiece(":", 1));
        continue;
      }
    yy123:
      yych = *(q = ++p);
      if (yybm[0 + yych] & 32) {
        goto yy127;
      }
      goto yy113;
    yy124:
      ++p;
      yych = *p;
      if (yybm[0 + yych] & 16) {
        goto yy124;
      }
      { continue; }
    yy127:
      ++p;
      yych = *p;
      if (yybm[0 + yych] & 32) {
        goto yy127;
      }
      if (yych == '}')
        goto yy130;
      p = q;
      goto yy113;
    yy130:
      ++p;
      {
        eval->AddSpecial(StringPiece(start + 2, p - start - 3));
        continue;
      }
    yy132:
      ++p;
      yych = *p;
    yy133:
      if (yybm[0 + yych] & 64) {
        goto yy132;
      }
      goto yy120;
    yy134:
      ++p;
      yych = *p;
      if (yych == ' ')
        goto yy134;
      { continue; }
    yy137:
      ++p;
      {
        if (path)
          p = start;
        break;
      }
    yy139:
      ++p;
      yych = *p;
    yy140:
      if (yybm[0 + yych] & 128) {
        goto yy139;
      }
      goto yy104;
    }
  }
  last_token_ = start;
  ofs_ = p;
  if (path)
    EatWhitespace();
  // Non-path strings end in newlines, so there's no whitespace to eat.
  return true;
}
