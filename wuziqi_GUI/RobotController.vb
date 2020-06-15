Class RobotController

    Public Declare Function NextMoveA Lib "RobotA.dll" Alias "GetNextMove" (ByRef map As Integer, ByVal move As Integer) As Integer
    Public Declare Sub ResetA Lib "RobotA.dll" Alias "Reset" ()
    Public Declare Sub SetColorA Lib "RobotA.dll" Alias "SetPlayerColor" (ByVal playerColor As Integer)
    Public Declare Function NextMoveB Lib "RobotB.dll" Alias "GetNextMove" (ByRef map As Integer, ByVal move As Integer) As Integer
    Public Declare Sub ResetB Lib "RobotB.dll" Alias "Reset" ()
    Public Declare Sub SetColorB Lib "RobotB.dll" Alias "SetPlayerColor" (ByVal playerColor As Integer)



    Public Property Mode As GameMode = GameMode.PVE
    Public Property CurrentBoard As Integer()
    Public Property CurrentMove As Integer

    Sub New()

    End Sub
    Sub Reset()

    End Sub

    Private Sub RobotControler_OnMove(robotIndex As Integer) Handles Me.OnMove
        Dim index As Integer
        Select Case robotIndex
            Case 0
                index = NextMoveA(CurrentBoard(0), 0)
            Case 1
                index = NextMoveB(CurrentBoard(0), Nothing)
        End Select

        FormMain.BtnChessBoard(index).PerformClick()
    End Sub

    Sub PerformMove(robotIndex As Integer)
        RaiseEvent OnMove(robotIndex)
    End Sub

    Event OnMove(robotIndex As Integer)
End Class