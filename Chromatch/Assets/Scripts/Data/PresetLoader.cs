using UnityEngine;
using System.Collections;

public class PresetLoader : MonoBehaviour {

	public void LoadPreset(int level) {
     switch (level) {
      case 0:
        CubeData easy = new CubeData(Dificulty.Easy, 3, 3, 3, 0.5);
        GetComponent<FileManager>().WriteCubeData(easy, "cubeData");
        break;
      case 1:
        CubeData med = new CubeData(Dificulty.Medium, 5, 5, 5, 0.5);
        GetComponent<FileManager>().WriteCubeData(med, "cubeData");
        break;
      case 2:
        CubeData hard = new CubeData(Dificulty.Hard, 10, 10, 10, 0.5);
        GetComponent<FileManager>().WriteCubeData(hard, "cubeData");
        break;
      default:
        CubeData def = new CubeData(Dificulty.Easy, 3, 3, 3, 0.5);
        GetComponent<FileManager>().WriteCubeData(def, "cubeData");
        break;
    }
  }
}
