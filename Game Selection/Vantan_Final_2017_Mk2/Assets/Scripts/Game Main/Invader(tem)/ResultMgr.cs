using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;

public class ResultMgr : MonoBehaviour
{

    // Use this for initialization
    void Start()
    {
        SoundMgr.SoundLoadSe("Push", "Invader/Push");
        SoundMgr.SoundLoadBgm("Result_A", "Invader/Result_A");
        SoundMgr.PlayBgm("Result_A");
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetAxis("BottomGreen") == 1)
        {
            SoundMgr.PlaySe("Push");
          SceneManager.LoadScene("InvaderTitle");
            SoundMgr.StopBgm();
        }
        if (Input.GetAxis("BottomRed") == 1)
        {
            SoundMgr.PlaySe("Push");
            SceneManager.LoadScene("MainTitle");
            SoundMgr.StopBgm();
        }
    }
}
