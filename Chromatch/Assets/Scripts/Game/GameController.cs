using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class GameController : MonoBehaviour {

  [SerializeField]
  private GameObject _changeTextObject = null;
  private Text _changeText;
  private int _changeCount;

  [SerializeField]
  private GameObject _timeTextObject = null;
  private Text _timeText;
  private float _timeCount;

  [SerializeField]
  private GameObject _resultCanvas = null;

  [SerializeField]
  private GameObject _particleEmitter = null;

  [SerializeField]
  private GameObject _SEPlayer = null;

  private Dificulty _currentDificulty;

  private RankingData _currentPlayRank;

  private GameObject[,,] cubes;
  private int _columnsMax;
  private int _rowsMax;
  private int _depthMax;

  private bool _cleared;

  void Start() {
    cubes = GetComponent<CoreController>().cube;
    _columnsMax = cubes.GetLength(0);
    _rowsMax = cubes.GetLength(1);
    _depthMax = cubes.GetLength(2);

    _changeText = _changeTextObject.GetComponent<Text>();
    _timeText = _timeTextObject.GetComponent<Text>();

    _currentDificulty = GetComponent<CoreController>().playDificulty;
    _currentPlayRank = new RankingData();
    _currentPlayRank.changeCount = new int[1];
    _currentPlayRank.timeCount = new int[1];

    UpdateText();
  }

  void Update() {
    for (var i = 0; i < _columnsMax; i++) {
      for (var j = 0; j < _rowsMax; j++) {
        for (var k = 0; k < _depthMax; k++) {
          CompareCubes(i, j, k);
        }
      }
    }
    if (!_cleared) {
      _timeCount += Time.deltaTime;
      UpdateText();
      if (_resultCanvas.activeSelf) {
        _resultCanvas.SetActive(false);
      }
      CheckClear();
    }
  }

  private void UpdateText() {
    _changeText.text = "Color Changes: " + _changeCount;
    _timeText.text = "Time: " + (int)_timeCount + " Seconds";
  }

  private void CompareCubes(int i, int j, int k) {
    if (cubes[i, j, k] == null) {
      return;
    }
    if (cubes[i, j, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
      CompareColumns(i, j, k);
      CompareRows(i, j, k);
      CompareDepth(i, j, k);
    }
  }

  private void CompareColumns(int i, int j, int k) {
    if (i == 0) {
      if (cubes[i + 1, j, k] != null) {
        if (cubes[i + 1, j, k].activeSelf) {
          if (cubes[i + 1, j, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i + 1, j, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i + 1, j, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else if (i == _columnsMax - 1) {
      if (cubes[i - 1, j, k] != null) {
        if (cubes[i - 1, j, k].activeSelf) {
          if (cubes[i - 1, j, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i - 1, j, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i - 1, j, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else /*0 < i < columnsMax*/{
      if (cubes[i + 1, j, k] != null && cubes[i - 1, j, k] != null) {
        if (cubes[i + 1, j, k].activeSelf && cubes[i - 1, j, k].activeSelf) {
          if (cubes[i + 1, j, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player &&
          cubes[i - 1, j, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i + 1, j, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i + 1, j, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }

            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i - 1, j, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i - 1, j, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }
  }

  private void CompareRows(int i, int j, int k) {
    if (j == 0) {
      if (cubes[i, j + 1, k] != null) {
        if (cubes[i, j + 1, k].activeSelf) {
          if (cubes[i, j + 1, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j + 1, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j + 1, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else if (j == _rowsMax - 1) {
      if (cubes[i, j - 1, k] != null) {
        if (cubes[i, j - 1, k].activeSelf) {
          if (cubes[i, j - 1, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j - 1, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j - 1, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else /*0 < j < rowsMax*/{
      if (cubes[i, j + 1, k] != null && cubes[i, j - 1, k] != null) {
        if (cubes[i, j + 1, k].activeSelf && cubes[i, j - 1, k].activeSelf) {
          if (cubes[i, j + 1, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player &&
          cubes[i, j - 1, k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j + 1, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j + 1, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }

            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j - 1, k].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j - 1, k].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }
  }

  private void CompareDepth(int i, int j, int k) {
    if (k == 0) {
      if (cubes[i, j, k + 1] != null) {
        if (cubes[i, j, k + 1].activeSelf) {
          if (cubes[i, j, k + 1].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j, k + 1].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j, k + 1].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else if (k == _depthMax - 1) {
      if (cubes[i, j, k - 1] != null) {
        if (cubes[i, j, k - 1].activeSelf) {
          if (cubes[i, j, k - 1].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j, k - 1].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j, k - 1].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }

    else /*0 < k < depthMax*/{
      if (cubes[i, j, k + 1] != null && cubes[i, j, k - 1] != null) {
        if (cubes[i, j, k + 1].activeSelf && cubes[i, j, k - 1].activeSelf) {
          if (cubes[i, j, k + 1].GetComponent<CubeManager>().cubeState == CubeManager.State.Player &&
          cubes[i, j, k - 1].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            return;
          }
          else {
            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j, k + 1].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j, k + 1].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }

            if (cubes[i, j, k].GetComponent<CubeManager>().cubeColor == cubes[i, j, k - 1].GetComponent<CubeManager>().cubeColor) {
              cubes[i, j, k - 1].GetComponent<CubeManager>().cubeState = CubeManager.State.Player;
            }
          }
        }
      }
    }
  }

  private void CheckClear() {
    for (var i = 0; i < _columnsMax; i++) {
      for (var j = 0; j < _rowsMax; j++) {
        for (var k = 0; k < _depthMax; k++) {
          if(cubes[i,j,k] == null) {
            continue;
          }
          else if(cubes[i,j,k].GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            continue;
          }
          else {
            return;
          }
        }
      }
    }
    _cleared = true;
    _currentPlayRank.changeCount[0] = _changeCount;
    _currentPlayRank.timeCount[0] = (int)_timeCount;
    _particleEmitter.SetActive(true);
    _resultCanvas.SetActive(true);
    _SEPlayer.GetComponent<SoundEffectPlayer>().PlaySE3();
  }

  public void ChangeColor(int color) {
    var core = GetComponent<CoreController>().cube;
    for (int i = 0; i < core.GetLength(0); i++) {
      for (int j = 0; j < core.GetLength(1); j++) {
        for (int k = 0; k < core.GetLength(2); k++) {
          if (core[i, j, k] == null) continue;
          var cube = core[i, j, k];
          if (cube.GetComponent<CubeManager>().cubeState == CubeManager.State.Player) {
            switch (color) {
              case 0:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Red;
                break;
              case 1:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Green;
                break;
              case 2:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Blue;
                break;
              case 3:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Yellow;
                break;
              case 4:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Cyan;
                break;
              case 5:
                cube.GetComponent<CubeManager>().cubeColor = CubeManager.CubeColor.Magenta;
                break;
            }
          }
        }
      }
    }
  }
  
  public void AddChangeCount() {
    _changeCount++;
  }

  public void CompareRanking() {
    if(_currentDificulty == Dificulty.Custom) {
      return;
    }
    RankingData ranking = new RankingData();
    switch (_currentDificulty) {
      case Dificulty.Easy:
        ranking = GetComponent<FileManager>().ReadRanking("easyRank");
        break;
      case Dificulty.Medium:
        ranking = GetComponent<FileManager>().ReadRanking("medRank");
        break;
      case Dificulty.Hard:
        ranking = GetComponent<FileManager>().ReadRanking("hardRank");
        break;
    }

    int[] changeCountRanking = new int[4];
    int[] timeCountRanking = new int[4];

    for(int i = 0; i < 3; i++) {
      changeCountRanking[i] = ranking.changeCount[i];
      timeCountRanking[i] = ranking.timeCount[i];
    }

    changeCountRanking[3] = _currentPlayRank.changeCount[0];
    timeCountRanking[3] = _currentPlayRank.timeCount[0];

    for(int i = 0; i < 4; i++) {
      for(int j = 0; j < 3; j++) {
        if (changeCountRanking[j] > changeCountRanking[j + 1]) {
          var temp = changeCountRanking[j];
          changeCountRanking[j] = changeCountRanking[j + 1];
          changeCountRanking[j + 1] = temp;
        }

        if (timeCountRanking[j] > timeCountRanking[j + 1]) {
          var temp = timeCountRanking[j];
          timeCountRanking[j] = timeCountRanking[j + 1];
          timeCountRanking[j + 1] = temp;
        }
      }
    }

    RankingData newRanking = new RankingData();
    newRanking.changeCount = new int[3];
    newRanking.timeCount = new int[3];

    for(int i = 0; i < 3; i++) {
      newRanking.changeCount[i] = changeCountRanking[i];
      newRanking.timeCount[i] = timeCountRanking[i];
    }

    switch (_currentDificulty) {
      case Dificulty.Easy:
        GetComponent<FileManager>().WriteRanking(newRanking, "easyRank");
        break;
      case Dificulty.Medium:
        GetComponent<FileManager>().WriteRanking(newRanking, "medRank");
        break;
      case Dificulty.Hard:
        GetComponent<FileManager>().WriteRanking(newRanking, "hardRank");
        break;
    }
  }

}
