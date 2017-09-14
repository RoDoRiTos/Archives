using System.IO;
using UnityEngine;

public enum Dificulty {
  Easy,
  Medium,
  Hard,
  Custom
}

public class CubeData {

  public CubeData() {
    dificulty = Dificulty.Easy;
    columns = 3;
    rows = 3;
    depth = 3;
    margin = 0.5f;
  }

  public CubeData(Dificulty dif, int c, int r, int d, double m) {
    dificulty = dif;
    columns = c;
    rows = r;
    depth = d;
    margin = m;
  }

  private Dificulty _dificulty;

  public Dificulty dificulty {
    get { return _dificulty; }
    set { _dificulty = value; }
  }


  private int _columns;

  public int columns {
    get { return _columns; }
    set { _columns = value; }
  }

  private int _rows;

  public int rows {
    get { return _rows; }
    set { _rows = value; }
  }
    
  private int _depth;

  public int depth {
    get { return _depth; }
    set { _depth = value; }
  }

  private double _margin;

  public double margin {
    get { return _margin; }
    set { _margin = value; }
  }

}

public class RankingData {

  private int[] _changeCount;

  public int[] changeCount {
    get { return _changeCount; }
    set { _changeCount = value; }
  }

  private int[] _timeCount;

  public int[] timeCount {
    get { return _timeCount; }
    set { _timeCount = value; }
  }

}

public class FileManager : MonoBehaviour {

  public CubeData ReadCubeData(string fileName) {
    var folderpath = Application.dataPath + "/CubeData/";
    var filePath = folderpath + fileName + ".json";

    if (!File.Exists(filePath)) return null;

    var jsonText = File.ReadAllText(filePath);
    if (string.IsNullOrEmpty(jsonText)) return null;
    
    var json = LitJson.JsonMapper.ToObject<CubeData>(jsonText);
    return json;
  }

  public void WriteCubeData(CubeData data, string fileName) {
    string json = LitJson.JsonMapper.ToJson(data);

    var path = Application.dataPath + "/CubeData/";

    // フォルダーがない場合は作成する
    if (!Directory.Exists(path)) {
      Directory.CreateDirectory(path);
    }
    File.WriteAllText(path + fileName + ".json", json);
  }

  public RankingData ReadRanking(string fileName) {
    var folderpath = Application.dataPath + "/RankingData/";
    var filePath = folderpath + fileName + ".json";

    if (!File.Exists(filePath)) return null;

    var jsonText = File.ReadAllText(filePath);
    if (string.IsNullOrEmpty(jsonText)) return null;

    var json = LitJson.JsonMapper.ToObject<RankingData>(jsonText);
    return json;
  }

  public void WriteRanking(RankingData data, string fileName) {
    string json = LitJson.JsonMapper.ToJson(data);

    var path = Application.dataPath + "/RankingData/";

    // フォルダーがない場合は作成する
    if (!Directory.Exists(path)) {
      Directory.CreateDirectory(path);
    }
    File.WriteAllText(path + fileName + ".json", json);
  }
}