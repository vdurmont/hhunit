<?hh // strict

use \HHUnit\Core\IFileService;

class InMemoryFolder {
  private string $name;
  private array<string, InMemoryFolder> $folders;
  private array<string> $files;

  public function __construct(string $name) {
    $this->name = $name;
    $this->folders = array();
    $this->files = array();
  }

  public function createFolder(string $name) : InMemoryFolder {
    $folder = new InMemoryFolder($name);
    $this->folders[$name] = $folder;
    return $folder;
  }

  public function createFile(string $name) : void {
    $this->files[] = $name;
  }

  public function getFolders() : array<string, InMemoryFolder> {
    return $this->folders;
  }

  public function getFiles() : array<string> {
    return $this->files;
  }
}

class InMemoryFileService implements IFileService {
  private array<string, InMemoryFolder> $folders;

  public function __construct() {
    $this->folders = array();
  }

  public function createFolder(string $name) : InMemoryFolder {
    $folder = new InMemoryFolder($name);
    $this->folders[$name] = $folder;
    return $folder;
  }

  public function getCwd() : string {
    throw new \Exception("Not implemented");
  }

  public function isDirectory(string $path) : bool {
    throw new \Exception("Not implemented");
  }

  public function isFile(string $path) : bool {
    $folder = null;
    $lastPart = null;
    try {
      $parts = explode("/", $path);
      $count = count($parts);
      $lastPart = $parts[$count - 1];
      $folder = $this->getFolderFromPath(implode("/", array_slice ($parts, 0, $count - 1)));
    } catch(\Exception $e) {
      $folder = null;
    }

    if ($folder !== null && $lastPart !== null) {
      return in_array($lastPart, $folder->getFiles());
    }

    throw new \Exception("Unable to find file.");
  }

  private function getFolderFromPath(string $path) : InMemoryFolder {
    $parts = explode("/", $path);
    $folder = NULL;
    $i = 0;
    while($i < count($parts)) {
      $part = $parts[$i];
      if ($part === "") {
        // Ignore the empty parts...
        $i++;
      } else {
        if ($folder === null) {
          // We look in the root folders of the FileSystem
          if (array_key_exists($part, $this->folders)) {
            $folder = $this->folders[$part];
            $i++;
          } else {
            throw new \Exception("Unable to find folder.");
          }
        } else {
          // We look in the subfolders
          if (array_key_exists($part, $folder->getFolders())) {
            $folder = $folder->getFolders()[$part];
            $i++;
          } else {
            throw new \Exception("Unable to find folder.");
          }
        }
      }
    }

    if ($folder === null) {
      throw new \Exception("Unable to find folder.");
    }
    return $folder;
  }

  public function scanDirectory(string $path) : array<string> {
    $folder = $this->getFolderFromPath($path);
    $res = array();
    foreach ($folder->getFolders() as $key => $value) {
      $tmp = explode("/", $key);
      $res[] = $tmp[count($tmp) - 1];
    }
    foreach ($folder->getFiles() as $value) {
      $tmp = explode("/", $value);
      $res[] = $tmp[count($tmp) - 1];
    }
    ksort($res);
    return $res;
  }

  public function getFileContent(string $path) : string {
    throw new \Exception("Not implemented");
  }
}
