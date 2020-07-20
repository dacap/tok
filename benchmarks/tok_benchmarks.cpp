// Tok Library
// Copyright (c) 2020 David Capello
//
// This file is released under the terms of the MIT license.
// Read LICENSE.txt for more information.

#include "../tok.h"
#include <benchmark/benchmark.h>

#include <cstring>
#include <map>
#include <string>
#include <vector>

std::map<int, std::string> strings;

static const char* create_string(int arg) {
  auto it = strings.find(arg);
  if (it != strings.end())
    return it->second.c_str();

  std::string str;
  for (int c=0; c<arg; ++c) {
    std::string word = " ";
    for (int i=1; i<(c%32); ++i) {
      word.push_back('a');
    }
    str += word;
  }
  strings[arg] = str;
  return strings[arg].c_str();
}

static void BM_StrTok(benchmark::State& state) {
  const char* str = create_string(state.range(0));
  size_t n = std::strlen(str)+1;
  std::vector<char> buf(n);
  for (auto _ : state) {
    state.PauseTiming();
    std::copy(str, str+n, buf.begin());
    state.ResumeTiming();
    for (auto tok=std::strtok(&buf[0], " "); tok; tok=std::strtok(nullptr, " ")) {
      // Do nothing
    }
  }
}
BENCHMARK(BM_StrTok)->Range(1, 4096);

static void split_string(const std::string& string,
                         std::vector<std::string>& parts)
{
  std::size_t elements = 1 + std::count(string.begin(), string.end(), ' ');
  parts.reserve(elements);

  std::size_t beg = 0, end;
  while (true) {
    end = string.find_first_of(' ', beg);
    if (end != std::string::npos) {
      parts.push_back(string.substr(beg, end - beg));
      beg = end+1;
    }
    else {
      parts.push_back(string.substr(beg));
      break;
    }
  }
}

static void BM_SplitString(benchmark::State& state) {
  const char* str = create_string(state.range(0));
  std::string s(str);
  for (auto _ : state) {
    std::vector<std::string> parts;
    split_string(s, parts);
  }
}
BENCHMARK(BM_SplitString)->Range(1, 4096);

static void BM_Tok(benchmark::State& state) {
  const char* str = create_string(state.range(0));
  std::string s(str);
  for (auto _ : state) {
    for (const auto& tok : tok::split_tokens(s, ' ')) {
      // Do nothing
    }
  }
}
BENCHMARK(BM_Tok)->Range(1, 4096);

BENCHMARK_MAIN();
