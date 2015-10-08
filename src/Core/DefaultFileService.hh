<?hh // strict

namespace HHUnit\Core;

/**
* FileService that works on the filesystem.
*/
class DefaultFileService implements IFileService {
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
