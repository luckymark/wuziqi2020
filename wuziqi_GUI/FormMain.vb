Public Class FormMain
    'global and const
    Const BOARD_BLOCK_SIZE As Integer = 40
    Const BOARD_INNER_MARGIN As Integer = 0
    Const BOARD_OUTER_MARGIN As Integer = 40
    Private Property Opt As ChessColor = ChessColor.Black
    Private Property Last_i As Integer = -1
    Private Property MoveCounter As Integer = 1
    Private currentBoard(224) As Integer
    Enum ChessColor
        White = 1
        Black = 2
    End Enum

    'out library

    Public Declare Function getCounter Lib "Dll_Test.dll" () As Integer



    Private Sub FormMain_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        'lock window
        Me.MaximumSize = Me.Size
        Me.MinimumSize = Me.Size

        'initialize chessboard
        InitializeChessboard()

    End Sub

    Sub InitializeChessboard()
        Dim tmp As MyButton
        PanelChessBoard.Height = 15 * BOARD_BLOCK_SIZE + 14 * BOARD_INNER_MARGIN + 2 * BOARD_OUTER_MARGIN
        PanelChessBoard.Width = PanelChessBoard.Height

        For i = 0 To 224
            tmp = New MyButton With {
                .Text = "",
                .BackColor = Me.BackColor,
                .BackgroundImage = My.Resources.chessboard.empty,
                .Index = i,
                .Left = BOARD_OUTER_MARGIN + (i Mod 15) * (BOARD_INNER_MARGIN + BOARD_BLOCK_SIZE),
                .Top = BOARD_OUTER_MARGIN + (i \ 15) * (BOARD_INNER_MARGIN + BOARD_BLOCK_SIZE),
                .Size = New Point(BOARD_BLOCK_SIZE, BOARD_BLOCK_SIZE),
                .FlatStyle = FlatStyle.Flat,
                .BackgroundImageLayout = ImageLayout.Stretch
            }
            tmp.FlatAppearance.BorderColor = Me.BackColor
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
        currentBoard(i) = Opt
        UpdateBtnBoard(i)
        MoveCounter += 1
    End Sub

    Private Sub UpdateBtnBoard(i As Integer)
        If Last_i <> -1 Then
            BtnChessBoard(Last_i).FlatAppearance.BorderColor = BtnChessBoard(i).BackColor
        End If
        Last_i = i

        If Opt = ChessColor.Black Then
            'black chess 
            BtnChessBoard(i).ForeColor = Color.White
            BtnChessBoard(i).BackgroundImage = My.Resources.chessboard.black
            Opt = ChessColor.White
        Else
            'white chess
            BtnChessBoard(i).ForeColor = Color.Black
            BtnChessBoard(i).BackgroundImage = My.Resources.chessboard.white
            Opt = ChessColor.Black
        End If
        BtnChessBoard(i).Text = MoveCounter.ToString()
        BtnChessBoard(i).FlatAppearance.BorderColor = Color.Blue
    End Sub

    Friend BtnChessBoard(224) As MyButton



    Class MyButton
        Inherits Button
        Property Index As Integer
    End Class


End Class
