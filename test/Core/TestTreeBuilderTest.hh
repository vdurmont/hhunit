<?hh // strict

use \HHUnit\Assert\Assert;
use \HHUnit\Core\TestTreeBuilder;
use \HHUnit\Core\ClassLoader;
use \HHUnit\Model\TestTree;

class TestTreeBuilderTest {
  <<SetUpClass>>
  public static function setUpClass() : void {
    ClassLoader::loadClass(__DIR__."/../../testResources/InMemoryFileService.hh");
  }

  <<Test>>
  public function buildTree_a_full_test() : void {
    // /my/project/test
    //      |- HHUnitSetUp.hh
    //      |- HHUnitTearDown.hh
    //      |- MyFirstTest.hh
    //      |- MySecondTest.hh
    //      |- /subfolder1
    //      |     |- HHUnitSetUp.hh
    //      |     |- MyTest.hh
    //      |     |- RandomFile1.hh
    //      |- /subfolder2
    //      |     |- HHUnitTearDown.hh
    //      |     |- MyOtherTest.hh
    //      |     |- RandomFile2.hh
    //      |- /subfolder3
    //      |     |- MyLastTest.hh
    //      |- /subfolder4
    //      |     |- RandomFile3.hh
    //      |     |
    //      |- /subfolder5
    //      |     |- /subsubfolder1
    //      |     |     |- /subsubsubfolder1
    //      |     |     |     |- HHUnitSetUp.hh
    //      |     |     |     |- MyFirstSubTest.hh
    //      |     |     |     |- MySecondSubTest.hh
    //      |- /subfolder6
    //      |     |- /subsubfolder2

    $fs = new InMemoryFileService();
    self::init($fs);

    $builder = new TestTreeBuilder($fs);
    $rootTree = $builder->buildTree("/my/project/test/");

    $tests = array("/my/project/test/MyFirstTest.hh", "/my/project/test/MySecondTest.hh");
    self::assertTree($rootTree, "/my/project/test", true, true, $tests, 6);

    $subfolder1 = $rootTree->getTestTree("/my/project/test/subfolder1");
    $tests = array("/my/project/test/subfolder1/MyTest.hh");
    self::assertTree($subfolder1, "/my/project/test/subfolder1", true, false, $tests, 0);

    $subfolder2 = $rootTree->getTestTree("/my/project/test/subfolder2");
    $tests = array("/my/project/test/subfolder2/MyOtherTest.hh");
    self::assertTree($subfolder2, "/my/project/test/subfolder2", false, true, $tests, 0);

    $subfolder3 = $rootTree->getTestTree("/my/project/test/subfolder3");
    $tests = array("/my/project/test/subfolder3/MyLastTest.hh");
    self::assertTree($subfolder3, "/my/project/test/subfolder3", false, false, $tests, 0);

    $subfolder4 = $rootTree->getTestTree("/my/project/test/subfolder4");
    $tests = array();
    self::assertTree($subfolder4, "/my/project/test/subfolder4", false, false, $tests, 0);

    $subfolder5 = $rootTree->getTestTree("/my/project/test/subfolder5");
    $tests = array();
    self::assertTree($subfolder5, "/my/project/test/subfolder5", false, false, $tests, 1);

    $subsubfolder1 = $subfolder5->getTestTree("/my/project/test/subfolder5/subsubfolder1");
    $tests = array();
    self::assertTree($subsubfolder1, "/my/project/test/subfolder5/subsubfolder1", false, false, $tests, 1);

    $subsubsubfolder1 = $subsubfolder1->getTestTree("/my/project/test/subfolder5/subsubfolder1/subsubsubfolder1");
    $tests = array("/my/project/test/subfolder5/subsubfolder1/subsubsubfolder1/MyFirstSubTest.hh", "/my/project/test/subfolder5/subsubfolder1/subsubsubfolder1/MySecondSubTest.hh");
    self::assertTree($subsubsubfolder1, "/my/project/test/subfolder5/subsubfolder1/subsubsubfolder1", true, false, $tests, 0);

    $subfolder6 = $rootTree->getTestTree("/my/project/test/subfolder6");
    $tests = array();
    self::assertTree($subfolder6, "/my/project/test/subfolder6", false, false, $tests, 1);

    $subsubfolder2 = $subfolder6->getTestTree("/my/project/test/subfolder6/subsubfolder2");
    $tests = array();
    self::assertTree($subsubfolder2, "/my/project/test/subfolder6/subsubfolder2", false, false, $tests, 0);
  }

  private static function assertTree(TestTree $tree, string $path, bool $hasSetUp, bool $hasTearDown, array<string> $tests, int $numSubTress) : void {
    Assert::equals($path, $tree->getPath());
    Assert::equals($hasSetUp, $tree->hasSetUp());
    Assert::equals($hasTearDown, $tree->hasTearDown());
    Assert::equals(count($tests), count($tree->getTestSuitesPaths()));
    foreach ($tests as $test) {
      Assert::arrayContains($test, $tree->getTestSuitesPaths());
    }
    Assert::equals($numSubTress, count($tree->getTestTrees()));
  }

  private static function init(InMemoryFileService $fs) : void {
    $root = $fs->createFolder("my");
    $root = $root->createFolder("project");
    $root = $root->createFolder("test");
    $root->createFile("HHUnitSetUp.hh");
    $root->createFile("HHUnitTearDown.hh");
    $root->createFile("MyFirstTest.hh");
    $root->createFile("MySecondTest.hh");
    $subfolder1 = $root->createFolder("subfolder1");
    $subfolder1->createFile("HHUnitSetUp.hh");
    $subfolder1->createFile("MyTest.hh");
    $subfolder1->createFile("RandomFile1.hh");
    $subfolder2 = $root->createFolder("subfolder2");
    $subfolder2->createFile("HHUnitTearDown.hh");
    $subfolder2->createFile("MyOtherTest.hh");
    $subfolder2->createFile("RandomFile2.hh");
    $subfolder3 = $root->createFolder("subfolder3");
    $subfolder3->createFile("MyLastTest.hh");
    $subfolder4 = $root->createFolder("subfolder4");
    $subfolder4->createFile("RandomFile3.hh");
    $subfolder5 = $root->createFolder("subfolder5");
    $subsubfolder1 = $subfolder5->createFolder("subsubfolder1");
    $subsubsubfolder1 = $subsubfolder1->createFolder("subsubsubfolder1");
    $subsubsubfolder1->createFile("HHUnitSetUp.hh");
    $subsubsubfolder1->createFile("MyFirstSubTest.hh");
    $subsubsubfolder1->createFile("MySecondSubTest.hh");
    $subfolder6 = $root->createFolder("subfolder6");
    $subfolder6->createFolder("subsubfolder2");
  }
}
