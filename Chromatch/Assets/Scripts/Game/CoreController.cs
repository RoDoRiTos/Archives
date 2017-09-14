using UnityEngine;
using System.Collections;

public class CoreController : MonoBehaviour {

  private int _columns = 3;

  public int columns {
    get { return _columns; }
    set { _columns = value; }
  }

  private int _rows = 3;

  public int rows {
    get { return _rows; }
    set { _rows = value; }
  }

  private int _depth = 3;

  public int depth {
    get { return _depth; }
    set { _depth = value; }
  }

  private double _margin = 0.5;

  public float margin {
    get { return (float)_margin; }
    set { _margin = value; }
  }

  private Dificulty _playDif;

  public Dificulty playDificulty {
    get { return _playDif; }
    set { _playDif = value; }
  }


  [SerializeField]
  private GameObject _objectPrefab = null;

  private GameObject[,,] _cube;

  public GameObject[,,] cube {
    get { return _cube; }
  }

  private bool _hasXCore = false;
  private bool _hasYCore = false;
  private bool _hasZCore = false;

  private void Awake() {
    var cubeData = GetComponent<FileManager>().ReadCubeData("cubeData");

    if (cubeData != null) {
      columns = cubeData.columns;
      rows = cubeData.rows;
      depth = cubeData.depth;
      _margin = cubeData.margin;
      playDificulty = cubeData.dificulty;
    }

    SetArray();
  }

  private void SetArray() {
    _cube = new GameObject[columns,rows,depth];

    CheckCores();
  }

  private void CheckCores() {
    if (_columns % 2 != 0) {
      _hasXCore = true;
    }
    else _hasXCore = false;

    if (_rows % 2 != 0) {
      _hasYCore = true;
    }
    else _hasYCore = false;

    if (_depth % 2 != 0) {
      _hasZCore = true;
    }
    else _hasZCore = false;
  }

  private void Start() {
    InitCubes();
  }

  private void InitCubes() {
    for (var i = 0; i < _cube.GetLength(0); i++) {
      for (var j = 0; j < _cube.GetLength(1); j++) {
        for (var k = 0; k < _cube.GetLength(2); k++) {
          var item = Instantiate(_objectPrefab);
          item.transform.parent = transform;
          item.name = string.Format("Object {0},{1},{2}", i, j, k);
          item.transform.Translate(new Vector3(SetObjectX(i), SetObjectY(j), SetObjectZ(k)));
          item.GetComponent<CubeManager>().SetRandomColor();
          if (i == 0 && j == 0 && k == 0) {
            item.GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
          }
          _cube[i,j,k] = item;
        }
      }
    }
    SetVisibleCubes();
    EraseInactiveCubes();
  }

  private float SetObjectX(int i) {
    if (_hasXCore) {
      int coreIndex = (columns - ((columns - 1) / 2)) - 1;
      if (i < coreIndex) {
        var minPos = -((columns - 1) / 2.0f) - margin * ((columns - 1) / 2.0f);
        return minPos + i + margin * i;
      }
      else if (i == coreIndex) {
        return 0;
      }
      else { /*i > corePos*/
        var index = i - coreIndex;
        return index + margin * index;
      }
    }
    else {
      var minPos = -(columns / 2) - margin * (columns / 2);
      //Margin Correction //Need to Fix
      minPos = minPos - minPos / columns;
      return minPos + i + margin * i;
    }
  }

  private float SetObjectY(int j) {
    if (_hasYCore) {
      int coreIndex = (rows - ((rows - 1) / 2)) - 1;
      if (j < coreIndex) {
        var minPos = -((rows - 1) / 2.0f) - margin * ((rows - 1) / 2.0f);
        return minPos + j + margin * j;
      }
      else if (j == coreIndex) {
        return 0;
      }
      else { /*j > coreIndex*/
        var index = j - coreIndex;
        return index + margin * index;
      }
    }
    else {
      var minPos = -(rows / 2) - margin * (rows / 2);
      //Margin Correction //Need to Fix
      minPos = minPos - minPos / rows;
      return minPos + j + margin * j;
    }
  }

  private float SetObjectZ(int k) {
    if (_hasZCore) {
      int coreIndex = (depth - ((depth - 1) / 2)) - 1;
      if (k < coreIndex) {
        var minPos = -((depth - 1) / 2.0f) - margin * ((depth - 1) / 2.0f);
        return minPos + k + margin * k;
      }
      else if (k == coreIndex) {
        return 0;
      }
      else { /*k > coreIndex*/
        var index = k - coreIndex;
        return index + margin * index;
      }
    }
    else {
      var minPos = -(depth / 2) - margin * (depth / 2);
      //Margin Correction //Need to Fix
      minPos = minPos - minPos / depth;
      return minPos + k + margin * k;
    }
  }

  private void SetVisibleCubes() {
    for (var i = 0; i < _columns; i++) {
      for (var j = 0; j < _rows; j++) {
        for (var k = 0; k < _depth; k++) {
          if (i != 0 && i != _columns - 1) {
            if (j != 0 && j != _rows - 1) {
              if (k != 0 && k != _depth - 1) {
                _cube[i,j,k].SetActive(false);
              }
            }
          }
        }
      }
    }
  }

  private void EraseInactiveCubes() {
    for (var i = 0; i < _columns; i++) {
      for (var j = 0; j < _rows; j++) {
        for (var k = 0; k < _depth; k++) {
          if (!_cube[i, j, k].activeSelf) {
            Destroy(_cube[i, j, k]);
            _cube[i, j, k] = null;
          }
        }
      }
    }
  }

}
