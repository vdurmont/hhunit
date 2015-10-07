<?hh // strict

namespace HHUnit\Model;

enum TestStatus : int {
  LOADING = 1;
  SUCCESS = 2;
  FAILURE = 3;
  SKIPPED = 4;
  ERROR = 5;
}
