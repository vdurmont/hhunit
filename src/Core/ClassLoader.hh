<?hh

namespace HHUnit\Core;

class ClassLoader {
  public static function loadClass(string $filePath) : void {
    require_once $filePath;
  }
}
