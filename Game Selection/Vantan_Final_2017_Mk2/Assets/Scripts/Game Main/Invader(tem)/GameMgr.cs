using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;



public static class STGGameState
{
    static int state = 0;

    public static void SetState(int val)
    {
        state = val;
    }

    public static int GetState()
    {
        return state;
    }
}


//ゲーム管理
public class GameMgr : MonoBehaviour
{
    //float activeTime;
    //float active;
    private void Start()
    {


    }
    void Update()
    {

    }

    public void Disable()
    {
    
    }
}
