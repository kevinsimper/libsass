#include <cstdio>
#include "document.hpp"

namespace Sass {

  Document::Document(string path, char* source)
  : path(path), source(source),
    line_number(1), own_source(false),
    context(*(new Context())),
    root(Node(1, Node::root)),
    // statements(vector<Node>()),
    lexed(Token())
  {
    // if (!source) read_file();
    if (!source) {
      std::FILE *f;
      // TO DO: CHECK f AGAINST NULL/0
      f = std::fopen(path.c_str(), "rb");
      std::fseek(f, 0, SEEK_END);
      int len = std::ftell(f);
      std::rewind(f);
      // TO DO: WRAP THE new[] IN A TRY/CATCH BLOCK
      source = new char[len + 1];
      std::fread(source, sizeof(char), len, f);
      source[len] = '\0';
      std::fclose(f);
      own_source = true;
    }
    position = source;
  }
  
  Document::Document(string path, Context& context)
  : path(path), source(source),
    line_number(1), own_source(false),
    context(context),
    root(Node(1, Node::root)),
    // statements(vector<Node>()),
    lexed(Token())
  {
    std::FILE *f;
    // TO DO: CHECK f AGAINST NULL/0
    f = std::fopen(path.c_str(), "rb");
    std::fseek(f, 0, SEEK_END);
    int len = std::ftell(f);
    std::rewind(f);
    // TO DO: WRAP THE new[] IN A TRY/CATCH BLOCK
    source = new char[len + 1];
    std::fread(source, sizeof(char), len, f);
    source[len] = '\0';
    std::fclose(f);
    own_source = true;
    position = source;
  }

  Document::~Document() {
    if (own_source) delete [] source;
    delete &context;
  }
  
}