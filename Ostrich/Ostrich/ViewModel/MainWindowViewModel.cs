using CommunityToolkit.Mvvm.ComponentModel;
using CommunityToolkit.Mvvm.Input;
using CommunityToolkit.Mvvm.Messaging;
using DevExpress.XtraSpreadsheet.Model;
using Microsoft.Extensions.DependencyInjection;
using Ostrich.Message;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;
using ViewModel;

namespace Ostrich.ViewModel
{
    public class MainWindowViewModel : ObservableRecipient, IRecipient<PopupMessage>
    {


        #region PrivateProperty
        private bool _IsPopupOpen = false;
        private object _PopupContent = null;
        private object _MainContent = null;
        private double _MessageWidth = 150;
        private double _MessageHeight = 150;
        #endregion


        #region Constructor

        public MainWindowViewModel() { 
            this.IsActive = true;

            this.MainContent = App.Current.Services.GetService<CalculatorViewModel>();


            ////Test
            //this.IsMainPopupOpen = true;
            //this.PopupMessageContent = App.Current.Services.GetService<MessageViewModel>();
            //this.MessageHeight = 500;
            //this.MessageWidth = 500;
            ////Test
        }
        #endregion


        #region Functions
        protected override void OnActivated()
        {
            Messenger.Register<PopupMessage>(this);
        }

        protected override void OnDeactivated()
        {
            Messenger.UnregisterAll(this);
        }

        #endregion


        #region Collection

        #endregion



        #region Public Property

        public bool IsPopupOpen
        {
            get => _IsPopupOpen;
            set => SetProperty(ref _IsPopupOpen, value);
        }


        public object PopupContent
        {
            get => _PopupContent;
            set => SetProperty(ref _PopupContent, value);
        }

        public object MainContent
        {
            get => _MainContent;
            set => SetProperty(ref _MainContent, value);
        }

        public double MessageWidth
        {
            get => _MessageWidth;
            set => SetProperty(ref _MessageWidth, value);
        }

        public double MessageHeight
        {
            get => _MessageHeight;
            set => SetProperty(ref _MessageHeight, value);
        }

        #endregion
 
        #region Command

        public ICommand PopUpCloseCommand
        {
            get => new RelayCommand(() =>
            {
                try
                {
                    this.IsPopupOpen = false;
                }catch(Exception ex)
                {
                    System.Diagnostics.Debug.WriteLine(ex.ToString());
                }
            });
        }


        #endregion

        #region Message Callback
        public void Receive(PopupMessage message)
        {
            try
            {
                this.PopupContent = null;
                switch (message.IsClose)
                {
                    case true:
                        this.IsPopupOpen = false;
                        break;
                    case false:
                        this.PopupContent = message.Content;
                        this.IsPopupOpen = true;
                        this.MessageWidth = message.MessageWidth;
                        this.MessageHeight = message.MessageHeight;
                        break;

                }
            }catch(Exception ex)
            {

                System.Diagnostics.Debug.WriteLine(ex.Message);
            }
        }
        #endregion
    }
}
