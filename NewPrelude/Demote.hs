{-# LANGUAGE DataKinds #-}
{-# LANGUAGE KindSignatures #-}




module Demote(
  Demoteℕ()
  )

  import Prelude()
  import Types

  import BinTypes

  newtype Demoteℕ (n :: ℕ) = DN ℕ

  dsucc :: Demoteℕ n -> Demoteℕ (Succ n)
  dsucc (DN n) = DN (Succ n)

  instance Boring (Demoteℕ Zero) where
    singVal = DN Zero
  instance Boring (Demoteℕ n) => Boring (Demoteℕ (Succ n)) where
    singVal = dsucc (singVal @(Demoteℕ n))
