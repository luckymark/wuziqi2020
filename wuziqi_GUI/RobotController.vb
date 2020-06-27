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

    Public Property CurrentRobot As Robot

    Sub New()
        ReDim CurrentBoard(224)
        If IO.File.Exists("RobotA.dll") Then
            CurrentRobot = Robot.A
        Else
            CurrentRobot = Robot.B
        End If
    End Sub

    Sub New(robotIndex As Robot)
        ReDim CurrentBoard(224)
        CurrentRobot = robotIndex
    End Sub

    Overloads Sub Reset()
        ResetA()
        ResetB()
    End Sub

    Overloads Sub Reset(robotIndex As Robot)
        Select Case robotIndex
            Case Robot.A
                ResetA()
            Case Robot.B
                ResetB()
        End Select
    End Sub

    Overloads Sub SetLevel(robotIndex As Robot, level As Integer)
        Select Case robotIndex
            Case Robot.A
                SetLevelA(level)
            Case Robot.B
                SetLevelB(level)
        End Select
    End Sub

    Overloads Sub SetLevel(levelA As Integer, levelB As Integer)
        SetLevelA(levelA)
        SetLevelB(levelB)
    End Sub

    Overloads Sub SetLevel(level As Integer)
        Select Case CurrentRobot
            Case Robot.A
                SetLevelA(level)
            Case Robot.B
                SetLevelB(level)
        End Select
    End Sub

    Overloads Sub SetColor(robotIndex As Robot, color As PlayerColor)
        Select Case robotIndex
            Case Robot.A
                SetColorA(color)
            Case Robot.B
                SetColorB(color)
        End Select
    End Sub

    Overloads Sub SetColor(color As PlayerColor)
        Select Case CurrentRobot
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

        FormMain.ShowResponseTime(dt.TotalSeconds)
        If Mode = GameMode.EVE Then ExchangeRobot()
        FormMain.RobotClick(index)



    End Sub

    Sub ExchangeRobot()
        If CurrentRobot = Robot.A Then
            CurrentRobot = Robot.B
        Else
            CurrentRobot = Robot.A
        End If
    End Sub

    Sub ClearBoard()
        ReDim CurrentBoard(224)
    End Sub

    Function GetJudgeState() As JudgeState
        Return Judge(CurrentBoard(0))
    End Function

    Overloads Sub PerformMove(robotIndex As Robot)
        RaiseEvent OnMove(robotIndex)
    End Sub

    Overloads Sub PerformMove()
        RaiseEvent OnMove(CurrentRobot)
    End Sub

    Event OnMove(robotIndex As Robot)

End Class