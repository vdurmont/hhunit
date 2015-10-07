<?hh // strict

namespace HHUnit\Core;

interface IConfigLoader {
  public function loadConfig() : Config;
}
