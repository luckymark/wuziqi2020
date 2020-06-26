Class RobotController

    Public Declare Function NextMoveA Lib "RobotA.dll" Alias "GetNextMove" (ByRef map As Integer, ByVal move As Integer) As Integer
    Public Declare Sub ResetA Lib "RobotA.dll" Alias "Reset" ()
    Public Declare Sub SetColorA Lib "RobotA.dll" Alias "SetColor" (ByVal playerColor As Integer)
    Public Declare Sub SetLevelA Lib "RobotA.dll" Alias "SetLevel" (ByVal level As Integer)

    Public Declare Function NextMoveB Lib "RobotB.dll" Alias "GetNextMove" (ByRef map As Integer, ByVal move As Integer) As Integer
    Public Declare Sub ResetB Lib "RobotB.dll" Alias "Reset" ()
    Public Declare Sub SetColorB Lib "RobotB.dll" Alias "SetColor" (ByVal playerColor As Integer)
    Public Declare Sub SetLevelB Lib "RobotB.dll" Alias "SetLevel" (ByVal level As Integer)

    Public Declare Function Judge Lib "wuziqi_Judge.dll" (ByRef map As Integer) As Integer

    Public Property Mode As GameMode = GameMode.PVE
    Public Property CurrentBoard As Integer()
    Public Property CurrentMove As Integer

    Sub New()
        ReDim CurrentBoard(224)
    End Sub
    Sub Reset(robotIndex As Robot)
        Select Case robotIndex
            Case Robot.A
                ResetA()
            Case Robot.B
                ResetB()
        End Select
    End Sub

    Sub SetLevel(robotIndex As Robot, level As Integer)
        Select Case robotIndex
            Case Robot.A
                SetLevelA(level)
            Case Robot.B
                SetLevelB(level)
        End Select
    End Sub

    Sub SetColor(robotIndex As Robot, color As PlayerColor)
        Select Case robotIndex
            Case Robot.A
                SetColorA(color)
            Case Robot.B
                SetColorB(color)
        End Select
    End Sub

    Private Sub RobotControler_OnMove(robotIndex As Robot) Handles Me.OnMove
        Dim index As Integer
        Dim t1, t2 As DateTime
        Dim dt As TimeSpan

        t1 = Now
        Select Case robotIndex
            Case Robot.A
                index = NextMoveA(CurrentBoard(0), CurrentMove)
            Case Robot.B
                index = NextMoveB(CurrentBoard(0), CurrentMove)
        End Select
        t2 = Now
        dt = t2 - t1
        FormMain.LblResponseTime.Text = "响应时间：" & dt.TotalSeconds & "s"

        FormMain.BtnChessBoard(index).PerformClick()

    End Sub

    Function GetJudgeState() As JudgeState
        Dim state As JudgeState = Judge(CurrentBoard(0))
        Return state
    End Function

    Function PerformMove(robotIndex As Robot) As Task
        RaiseEvent OnMove(robotIndex)
        Return Nothing
    End Function

    Event OnMove(robotIndex As Robot)

End Class