Public Class FormMain
    'global and const
    Const BOARD_BLOCK_SIZE As Integer = 40
    Const BOARD_INNER_MARGIN As Integer = 0
    Const BOARD_OUTER_MARGIN As Integer = 40
    Private Property CurrentPlayerColor As PlayerColor = PlayerColor.Black
    Private Property Last_i As Integer = -1
    Private Property MoveCounter As Integer = 1

    Private ReadOnly imgChessBlack As Bitmap = My.Resources.chessboard.black
    Private ReadOnly imgChessWhite As Bitmap = My.Resources.chessboard.white
    Private ReadOnly imgChessEmpty As Bitmap = My.Resources.chessboard.empty

#Region "机器人接口"



    'unit test
    Public Declare Function UnitTest Lib "wuziqi_Robot.dll" () As Integer

    'function of Robot

    WithEvents MyRobotController As RobotController
#End Region

#Region "棋盘UI"
    Sub InitializeChessboard()
        Dim tmp As MyButton
        PanelChessBoard.Height = 15 * BOARD_BLOCK_SIZE + 14 * BOARD_INNER_MARGIN + 2 * BOARD_OUTER_MARGIN
        PanelChessBoard.Width = PanelChessBoard.Height
        PanelChessBoard.BackColor = Color.LightGray

        For i = 0 To 224
            tmp = New MyButton With {
                .Text = "",
                .BackColor = Color.LightGray,
                .BackgroundImage = imgChessEmpty,
                .Index = i,
                .Left = BOARD_OUTER_MARGIN + (i Mod 15) * (BOARD_INNER_MARGIN + BOARD_BLOCK_SIZE),
                .Top = BOARD_OUTER_MARGIN + (i \ 15) * (BOARD_INNER_MARGIN + BOARD_BLOCK_SIZE),
                .Size = New Point(BOARD_BLOCK_SIZE, BOARD_BLOCK_SIZE),
                .FlatStyle = FlatStyle.Flat,
                .BackgroundImageLayout = ImageLayout.Stretch
            }
            tmp.FlatAppearance.BorderColor = Color.LightGray
            AddHandler tmp.Click, AddressOf ChessBoard_Click
            BtnChessBoard(i) = tmp
            PanelChessBoard.Controls.Add(tmp)
        Next

    End Sub

    Private Sub ChessBoard_Click(sender As Object, e As EventArgs)
        Dim i As Integer = sender.Index
        If BtnChessBoard(i).Text <> "" Then
            Exit Sub
        End If
        If CurrentPlayerColor = PlayerColor.Black Then
            MyRobotController.CurrentBoard(i) = ChessColor.Black
        Else
            MyRobotController.CurrentBoard(i) = ChessColor.White
        End If
        UpdateBtnBoard(i)
        MoveCounter += 1

        Select Case MyRobotController.Mode
            Case GameMode.PVP

            Case GameMode.PVE
                If RdiPVEBlackPlayer.Checked Xor CurrentPlayerColor = PlayerColor.Black Then
                    MyRobotController.PerformMove(RdiPVERobotB.Checked)
                End If
            Case GameMode.EVE
                MyRobotController.PerformMove(i)
        End Select

    End Sub

    Private Sub UpdateBtnBoard(i As Integer)
        Last_i = i

        If CurrentPlayerColor = PlayerColor.Black Then
            'black chess 
            BtnChessBoard(i).ForeColor = Color.White
            BtnChessBoard(i).BackgroundImage = imgChessBlack
            CurrentPlayerColor = PlayerColor.White
        Else
            'white chess
            BtnChessBoard(i).ForeColor = Color.Black
            BtnChessBoard(i).BackgroundImage = imgChessWhite
            CurrentPlayerColor = PlayerColor.Black
        End If
        BtnChessBoard(i).Text = MoveCounter.ToString()
    End Sub

    Sub ClearBoard()
        For Each s In BtnChessBoard
            s.BackgroundImage = imgChessEmpty
            s.Text = ""
            s.FlatAppearance.BorderColor = Color.LightGray
        Next
        CurrentPlayerColor = PlayerColor.Black
        Last_i = -1
        MoveCounter = 1
    End Sub

    Friend BtnChessBoard(224) As MyButton
    Class MyButton
        Inherits Button
        Property Index As Integer
    End Class
#End Region

#Region "其他UI"
    Private Sub FormMain_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'lock window
        Me.MaximumSize = Me.Size
        Me.MinimumSize = Me.Size

        'initialize chessboard
        InitializeChessboard()

        'init robot
        UpdateRobotState()
        MyRobotController = New RobotController

    End Sub

    Sub UpdateRobotState()
        Dim A_Exist, B_Exist As Boolean
        A_Exist = IO.File.Exists("RobotA.dll")
        B_Exist = IO.File.Exists("RobotB.dll")
        SetRobotRelevantUI(0, A_Exist)
        SetRobotRelevantUI(1, B_Exist)
        SetRobotRelevantUI(2, A_Exist Or B_Exist)
        SetRobotRelevantUI(3, A_Exist And B_Exist)

        If A_Exist Then
            LblIsAExist.Text = "就绪"
        Else
            LblIsAExist.Text = "缺失"
        End If
        If B_Exist Then
            LblIsBExist.Text = "就绪"
        Else
            LblIsBExist.Text = "缺失"
        End If

        If (Not A_Exist) And B_Exist Then
            RdiPVERobotB.Checked = True
        End If

    End Sub

    Sub SetRobotRelevantUI(index As Integer, state As Boolean)
        Select Case index
            Case 0  'Robot A
                TxtRobotNameA.Enabled = state
                TxtRobotLevelA.Enabled = state
                RdiPVERobotA.Enabled = state
            Case 1   'Robot B
                TxtRobotNameB.Enabled = state
                TxtRobotLevelB.Enabled = state
                RdiPVERobotB.Enabled = state
            Case 2   'Either A or B relevant
                RdiModePVE.Enabled = state
            Case 3   'Both A and B exists
                RdiModeEVE.Enabled = state
        End Select
    End Sub

    Private Sub BtnStart_Click(sender As Object, e As EventArgs) Handles BtnStart.Click
        'check robot
        UpdateRobotState()
        If (RdiModePVE.Checked And LblIsAExist.Text = "缺失" And LblIsBExist.Text = "缺失") Or RdiModeEVE.Checked And (LblIsAExist.Text = "缺失" Or LblIsBExist.Text = "缺失") Then
            MessageBox.Show("没有可用的robot")
            Exit Sub
        End If

        'init UI
        ClearBoard()
        PanelChessBoard.Enabled = True
        If RdiModePVP.Checked Or RdiModePVE.Checked Then
            BtnGiveUp.Enabled = True
            BtnUndo.Enabled = True
            BtnTip.Enabled = True
        ElseIf RdiModeEVE.Checked Then
            BtnStopEVE.Enabled = True
            BtnPause.Enabled = True
        Else
            Throw New Exception("没有选中游戏模式")
        End If

        'set robot
        If RdiModePVE.Checked Then
            MyRobotController.Reset()
            If RdiPVEBlackRobot.Checked Then
                Dim robotIndex As Integer
                If RdiPVERobotA.Checked Then
                    robotIndex = 0
                Else
                    robotIndex = 1
                End If
                MyRobotController.PerformMove(robotIndex)
            End If
        ElseIf RdiModeEVE.Checked Then
            MyRobotController.Reset()
            MyRobotController.PerformMove(0)
        End If

        BtnStart.Enabled = False
        GroupGlobalSetting.Enabled = False
    End Sub

    Private Sub RdiModePVP_CheckedChanged(sender As Object, e As EventArgs) Handles RdiModePVP.CheckedChanged
        If RdiModePVP.Checked Then
            GpBoxPVPSet.Enabled = True
            GpBoxPVESet.Enabled = False
            GpBoxEVESet.Enabled = False
        End If
    End Sub

    Private Sub RdiModePVE_CheckedChanged(sender As Object, e As EventArgs) Handles RdiModePVE.CheckedChanged
        If RdiModePVE.Checked Then
            GpBoxPVPSet.Enabled = False
            GpBoxPVESet.Enabled = True
            GpBoxEVESet.Enabled = False
        End If
    End Sub

    Private Sub RdiModeEVE_CheckedChanged(sender As Object, e As EventArgs) Handles RdiModeEVE.CheckedChanged
        If RdiModeEVE.Checked Then
            GpBoxPVPSet.Enabled = False
            GpBoxPVESet.Enabled = False
            GpBoxEVESet.Enabled = True
        End If
    End Sub

    Private Sub BtnPVPExchangeColor_Click(sender As Object, e As EventArgs) Handles BtnPVPExchangeColor.Click
        Dim s As String = TxtPVPBlackName.Text
        TxtPVPBlackName.Text = TxtPVPWhiteName.Text
        TxtPVPWhiteName.Text = s
    End Sub

    Private Sub BtnGiveUp_Click(sender As Object, e As EventArgs) Handles BtnGiveUp.Click
        ClearBoard()
        PanelChessBoard.Enabled = False
        GroupGlobalSetting.Enabled = True

        BtnStart.Enabled = True
        BtnGiveUp.Enabled = False
        BtnTip.Enabled = False
        BtnUndo.Enabled = False

    End Sub

    Private Sub BtnPause_Click(sender As Object, e As EventArgs) Handles BtnPause.Click
        If BtnPause.Text = "暂停" Then


            BtnPause.Text = "继续"
        Else



            BtnPause.Text = "暂停"
        End If
    End Sub

    Private Sub BtnStopEVE_Click(sender As Object, e As EventArgs) Handles BtnStopEVE.Click
        ClearBoard()
        PanelChessBoard.Enabled = False
        GroupGlobalSetting.Enabled = True

        BtnStart.Enabled = True
        BtnPause.Enabled = False
        BtnStopEVE.Enabled = False


    End Sub

    Private Sub BtnUndo_Click(sender As Object, e As EventArgs) Handles BtnUndo.Click

    End Sub

#End Region

    Private Sub ButtonUnitTest_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            Dim a As Integer = UnitTest()
            MessageBox.Show(a.ToString)
        Catch ex As Exception
            MessageBox.Show(ex.ToString)
        End Try
    End Sub


End Class
Enum GameMode
    PVP
    PVE
    EVE
End Enum

Enum PlayerColor
    Black = 1
    White = 2
End Enum
Enum ChessColor
    Empty = 0
    Black = 1
    White = 2
End Enum


