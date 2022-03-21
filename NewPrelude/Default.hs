{-# LANGUAGE FlexibleInstances
           , UndecidableInstances
           #-}

module Default where
import Prelude()
import NewPrelude

class Default d where
  def :: d

instance Monoid m => Default m where
  def = id
