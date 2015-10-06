<?hh

namespace HHUnit\Utils;

class FileService {
  public function isDirectory($path) : bool {
    return is_dir($path);
  }

  public function isFile($path) : bool {
    return is_file($path);
  }

  public function scanDirectory($path) : array<string> {
    return scandir($path);
  }
}
