<?hh

namespace HHUnit\Runner;

class ClassLoader {
  public static function loadClass(string $filePath) : void {
    require_once $filePath;
  }
}
