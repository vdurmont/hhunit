<?hh

namespace HHUnit;

class HHUnitLoader {
  public static function loadPath(string $path) : void {
    $files = scandir($path);
    foreach($files as $file) {
      $fullPath = $path."/".$file;
      if (is_dir($fullPath) && $file != "." && $file != "..") {
        HHUnitLoader::loadPath($fullPath);
      } else if (is_file($fullPath) && $file != "." && $file != ".." && $file != "autoload.php") {
        require_once($fullPath);
      }
    }
  }
}

HHUnitLoader::loadPath(__DIR__);
