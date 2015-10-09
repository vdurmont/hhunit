<?hh // strict

namespace HHUnit\Core;

/**
* Service used to wrap all the access to the FileSystem.
* Can be implemented to connect to a remote server, mock...
*/
interface IFileService {
  public function getCwd() : string;

  public function getRealpath(string $path) : string;

  public function isDirectory(string $path) : bool;

  public function isFile(string $path) : bool;

  public function scanDirectory(string $path) : array<string>;

  public function getFileContent(string $path) : string;
}
