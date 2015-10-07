<?hh // strict

namespace HHUnit\Core;

/**
* Service used to wrap all the access to the FileSystem.
* Can be overridden to connect to a remote server, mock...
*/
class FileService {
  public function getCwd() : string {
    return getcwd();
  }

  public function isDirectory(string $path) : bool {
    return is_dir($path);
  }

  public function isFile(string $path) : bool {
    return is_file($path);
  }

  public function scanDirectory(string $path) : array<string> {
    return scandir($path);
  }

  public function getFileContent(string $path) : string {
    return file_get_contents($path);
  }
}
