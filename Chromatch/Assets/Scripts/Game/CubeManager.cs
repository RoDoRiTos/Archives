using UnityEngine;
using System.Collections;

public class CubeManager : MonoBehaviour {

  public enum State {
    Player,
    Neutral
  }

  public enum CubeColor {
    NULL,
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta
  }

  [SerializeField]
  private Material _redMaterial = null;
  [SerializeField]
  private Material _greenMaterial = null;
  [SerializeField]
  private Material _blueMaterial = null;
  [SerializeField]
  private Material _yellowMaterial = null;
  [SerializeField]
  private Material _cyanMaterial = null;
  [SerializeField]
  private Material _magentaMaterial = null;

  [SerializeField]
  private Material _metalRedMaterial = null;
  [SerializeField]
  private Material _metalGreenMaterial = null;
  [SerializeField]
  private Material _metalBlueMaterial = null;
  [SerializeField]
  private Material _metalYellowMaterial = null;
  [SerializeField]
  private Material _metalCyanMaterial = null;
  [SerializeField]
  private Material _metalMagentaMaterial = null;

  private State _state = State.Neutral;

  public State cubeState {
    get { return _state; }
    set { _state = value; }
  }

  private State _lastFrameState = State.Neutral;

  private CubeColor _color = CubeColor.NULL;

  public CubeColor cubeColor {
    get { return _color; }
    set { _color = value; }
  }

  private CubeColor _lastFrameColor = CubeColor.NULL;

  private Renderer rend;


  void Start() {
    rend = GetComponent<Renderer>();
  }

  void Update() {
    if(_lastFrameState != cubeState) {
      if(cubeState == State.Player) {
        GetComponent<Rotator>().enabled = true;
        tag = "Player";
      }
    }
    UpdateColor();
  }

  public void SetRandomColor() {
    int temp = Random.Range(0, 6);

    switch (temp) {
      case 0:
        cubeColor = CubeColor.Red;
        break;
      case 1:
        cubeColor = CubeColor.Green;
        break;
      case 2:
        cubeColor = CubeColor.Blue;
        break;
      case 3:
        cubeColor = CubeColor.Yellow;
        break;
      case 4:
        cubeColor = CubeColor.Cyan;
        break;
      case 5:
        cubeColor = CubeColor.Magenta;
        break;
    }
  }

  private void UpdateColor() {
    if (_lastFrameColor == cubeColor && _lastFrameState == cubeState) return;
    switch (cubeColor) {
      case CubeColor.Red:
        if (_redMaterial == null) {
          rend.material.color = Color.red;
        }
        else if (_metalRedMaterial != null) { 
          if (cubeState == State.Player) {
            rend.material = _metalRedMaterial;
          }
          else rend.material = _redMaterial;
        }
        else rend.material = _redMaterial;
        break;

      case CubeColor.Green:
        if (_greenMaterial == null) {
          rend.material.color = Color.green;
        }
        else if (_metalGreenMaterial != null) {
          if (cubeState == State.Player) {
            rend.material = _metalGreenMaterial;
          }
          else rend.material = _greenMaterial;
        }
        else rend.material = _greenMaterial;
        break;

      case CubeColor.Blue:
        if (_blueMaterial == null) {
          rend.material.color = Color.blue;
        }
        else if (_metalBlueMaterial != null) {
          if (cubeState == State.Player) {
            rend.material = _metalBlueMaterial;
          }
          else rend.material = _blueMaterial;
        }
        else rend.material = _blueMaterial;
        break;

      case CubeColor.Yellow:
        if (_yellowMaterial == null) {
          rend.material.color = Color.yellow;
        }
        else if (_metalYellowMaterial != null) {
          if (cubeState == State.Player) {
            rend.material = _metalYellowMaterial;
          }
          else rend.material = _yellowMaterial;
        }
        else rend.material = _yellowMaterial;
        break;

      case CubeColor.Cyan:
        if (_cyanMaterial == null) {
          rend.material.color = Color.cyan;
        }
        else if (_metalCyanMaterial != null) {
          if (cubeState == State.Player) {
            rend.material = _metalCyanMaterial;
          }
          else rend.material = _cyanMaterial;
        }
        else rend.material = _cyanMaterial;
        break;

      case CubeColor.Magenta:
        if (_magentaMaterial == null) {
          rend.material.color = Color.magenta;
        }
        else if (_metalMagentaMaterial != null) {
          if (cubeState == State.Player) {
            rend.material = _metalMagentaMaterial;
          }
          else rend.material = _magentaMaterial;
        }
        else rend.material = _magentaMaterial;
        break;
    }
    _lastFrameColor = cubeColor;
  }
}
