<?hh // strict

namespace HHUnit\Model;

enum LifecycleIdentifier : int {
  SET_UP_CLASS = 1;
  SET_UP = 2;
  TEAR_DOWN = 3;
  TEAR_DOWN_CLASS = 4;
}
