Public Class FormMain
    'global and const
    Const BOARD_BLOCK_SIZE As Integer = 40
    Const BOARD_INNER_MARGIN As Integer = 0
    Const BOARD_OUTER_MARGIN As Integer = 40
    Private Property currentPlayerColor As PlayerColor = PlayerColor.Black
    Private Property Last_i As Integer = -1
    Private Property MoveCounter As Integer = 1
    Private currentBoard(224) As Integer
    Private imgChessBlack As Bitmap = My.Resources.chessboard.black
    Private imgChessWhite As Bitmap = My.Resources.chessboard.white
    Private imgChessEmpty As Bitmap = My.Resources.chessboard.empty

    Enum PlayerColor
        Black = 1
        White = 2
    End Enum
    Enum ChessColor
        Empty = 0
        Black = 1
        White = 2
    End Enum

    'function of Robot
    Public Declare Function getCounter Lib "Dll_Test.dll" () As Integer
    Public Declare Function UnitTest Lib "wuziqi_Robot.dll" () As Integer

    Private Sub FormMain_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'lock window
        Me.MaximumSize = Me.Size
        Me.MinimumSize = Me.Size

        'initialize chessboard
        InitializeChessboard()

        'check if robot exist

        'check if robot support black ban



    End Sub

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
        currentBoard(i) = currentPlayerColor
        UpdateBtnBoard(i)
        MoveCounter += 1
    End Sub

    Private Sub UpdateBtnBoard(i As Integer)
        Last_i = i

        If currentPlayerColor = PlayerColor.Black Then
            'black chess 
            BtnChessBoard(i).ForeColor = Color.White
            BtnChessBoard(i).BackgroundImage = imgChessBlack
            currentPlayerColor = PlayerColor.White
        Else
            'white chess
            BtnChessBoard(i).ForeColor = Color.Black
            BtnChessBoard(i).BackgroundImage = imgChessWhite
            currentPlayerColor = PlayerColor.Black
        End If
        BtnChessBoard(i).Text = MoveCounter.ToString()
    End Sub

    Friend BtnChessBoard(224) As MyButton



    Class MyButton
        Inherits Button
        Property Index As Integer
    End Class



    Private Sub BtnStart_Click(sender As Object, e As EventArgs) Handles BtnStart.Click
        'init UI
        ClearBoard()

        PanelChessBoard.Enabled = True
        If RdiModePVP.Checked Or RdiModePVE.Checked Then
            BtnGiveUp.Enabled = True
            BtnUndo.Enabled = True
            BtnTip.Enabled = True
        End If
        If RdiModeEVE.Checked Then
            BtnStopEVE.Enabled = True
            BtnPause.Enabled = True
        End If
        BtnStart.Enabled = False
        GroupGlobalSetting.Enabled = False

        'set robot
        If RdiModePVE.Checked Then

        ElseIf RdiModeEVE.Checked Then

        End If




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

    Sub ClearBoard()
        For Each s In BtnChessBoard
            s.BackgroundImage = imgChessEmpty
            s.Text = ""
            s.FlatAppearance.BorderColor = Color.LightGray
        Next
        currentPlayerColor = PlayerColor.Black
        Last_i = -1
        MoveCounter = 1
    End Sub

    Private Sub Button1_Click(sender As Object, e As EventArgs) Handles Button1.Click
        Try
            Dim a As Integer = UnitTest()
            MessageBox.Show(a.ToString)
        Catch ex As Exception
            MessageBox.Show(ex.ToString)
        End Try
    End Sub
End Class
