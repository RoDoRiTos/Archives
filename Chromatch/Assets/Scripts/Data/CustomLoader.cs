using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public struct DataText {
  public Text columns;
  public Text rows;
  public Text depth;
  public Text margin;
}

public class CustomLoader : MonoBehaviour {

  private CubeData _currentCubeData;
  private CubeData _newCubeData;

  private GameObject _currentData;
  private GameObject _newData;

  private DataText _currentText;
  private DataText _newText;

	private void Start () {
    _currentCubeData = GetComponent<FileManager>().ReadCubeData("cubeData");
    _newCubeData = _currentCubeData;
    _newCubeData.dificulty = Dificulty.Custom;
    _currentData = GameObject.Find("Current Data");
    _newData = GameObject.Find("New Data");

    _currentText.columns = _currentData.transform.Find("Columns").GetComponent<Text>();
    _currentText.rows = _currentData.transform.Find("Rows").GetComponent<Text>();
    _currentText.depth = _currentData.transform.Find("Depth").GetComponent<Text>();
    _currentText.margin = _currentData.transform.Find("Margin").GetComponent<Text>();

    _currentText.columns.text = "Current Columns: " + _currentCubeData.columns.ToString();
    _currentText.rows.text = "Current Rows: " + _currentCubeData.rows.ToString();
    _currentText.depth.text = "Current Depth: " + _currentCubeData.depth.ToString();
    _currentText.margin.text = "Current Margin: " + _currentCubeData.margin.ToString();

    _newText.columns = _newData.transform.Find("Columns").GetComponent<Text>();
    _newText.rows = _newData.transform.Find("Rows").GetComponent<Text>();
    _newText.depth = _newData.transform.Find("Depth").GetComponent<Text>();
    _newText.margin = _newData.transform.Find("Margin").GetComponent<Text>();
  }

	private void Update () {
    UpdateText();
	}

  private void UpdateText() {
    _newText.columns.text = "Custom Columns: " + _newCubeData.columns.ToString();
    _newText.rows.text = "Custom Rows: " + _newCubeData.rows.ToString();
    _newText.depth.text = "Custom Depth: " + _newCubeData.depth.ToString();
    _newText.margin.text = "Custom Margin: " + _newCubeData.margin.ToString();
  }

  public void ChangeColumns(int value) {
    _newCubeData.columns += value;

    if (_newCubeData.columns < 2) {
      _newCubeData.columns = 2;
    }

    if (_newCubeData.columns > 20) {
      _newCubeData.columns = 20;
    }

  }

  public void ChangeRows(int value) {
    _newCubeData.rows += value;

    if (_newCubeData.rows < 2) {
      _newCubeData.rows = 2;
    }

    if (_newCubeData.rows > 20) {
      _newCubeData.rows = 20;
    }

  }

  public void ChangeDepth(int value) {
    _newCubeData.depth += value;

    if (_newCubeData.depth < 2) {
      _newCubeData.depth = 2;
    }

    if (_newCubeData.depth > 20) {
      _newCubeData.depth = 20;
    }

  }

  public void ChangeMargin(float value) {
    _newCubeData.margin += value;

    if (_newCubeData.margin < 0.5f) {
      _newCubeData.margin = 0.5f;
    }

    if (_newCubeData.margin > 2.0f) {
      _newCubeData.margin = 2.0f;
    }

  }

  public void WriteData() {
    GetComponent<FileManager>().WriteCubeData(_newCubeData, "cubeData");
    _currentCubeData = _newCubeData;
    _currentText.columns.text = "Current Columns: " + _currentCubeData.columns.ToString();
    _currentText.rows.text = "Current Rows: " + _currentCubeData.rows.ToString();
    _currentText.depth.text = "Current Depth: " + _currentCubeData.depth.ToString();
    _currentText.margin.text = "Current Margin: " + _currentCubeData.margin.ToString();
  }
}
